import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT symbol, price, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) >= 1;",
        user_id,
    )
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    total = cash
    for stock in stocks:
        total += stock["price"] * stock["total_shares"]
    return render_template("index.html", stocks=stocks, cash=cash, total=total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol is None:
            return apology("Please enter a symbol")
        symbol = symbol.upper()

        item = lookup(symbol)
        if item is None:
            return apology("Invalid symbol")

        shares_str = request.form.get("shares")
        if not shares_str or not shares_str.isdigit():
            return apology("Shares must be a positive integer!")

        shares = int(shares_str)

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        item_symbol = item["symbol"]
        item_price = item["price"]
        total_price = item_price * shares

        if cash < total_price:
            return apology("Not enough cash")
        else:
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id
            )
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES(?, ?, ?, ?, ?)",
                user_id,
                item_symbol,
                shares,
                item_price,
                "buy",
            )
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT type, symbol, price, shares, time FROM transactions WHERE user_id = ?",
        user_id,
    )
    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Must provide a username", 403)

        elif not request.form.get("password"):
            return apology("Must provide a password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not rows[0]["hash"]:
            return apology("Invalid username and/or password", 403)

        stored_password = rows[0]["hash"]
        entered_password = request.form.get("password")

        if entered_password is None:
            return apology("Must provide a password", 403)

        if not check_password_hash(stored_password, entered_password):
            return apology("Invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("quote.html")

    # User reached route via POST (as by submitting a form via POST)
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("Please enter a symbol")

    item = lookup(symbol)

    if not item:
        return apology("Invalid symbol")

    return render_template(
        "quoted.html",
        item=item,
        usd=usd,
    )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirm_password = request.form.get("confirmation")

    if not username:
        return apology("You should input the username")
    elif not password:
        return apology("You should input your password")
    elif not confirm_password:
        return apology(
            "You should input your password again in 'Confirmation Password'"
        )
    elif password != confirm_password:
        return apology("Password does not match")

    password_hash = generate_password_hash(password)
    try:
        db.execute(
            "INSERT INTO users(username, hash) VALUES(?, ?)", username, password_hash
        )
    except Exception:
        return apology("Username already taken")

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_str = request.form.get("shares")
        if not shares_str or not shares_str.isdigit():
            return apology("Shares must be a positive integer!")

        shares = int(shares_str)
        if shares <= 0:
            return apology("Shares must be a positive number!")

        result = lookup(symbol)
        if result is None:
            return apology("Invalid symbol")

        item_price = result["price"]
        item_symbol = result["symbol"]

        shares_owned = db.execute(
            "SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?",
            user_id,
            symbol,
        )[0]["SUM(shares)"]
        print(shares_owned)
        print(shares)
        if shares_owned < shares:
            return apology("Not enough shares")

        if (shares_owned - shares) < 0:
            return apology("Not enough shares")

        price = shares * item_price
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", current_cash + price, user_id
        )
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES(?, ?, ?, ?, ?)",
            user_id,
            item_symbol,
            -shares,
            item_price,
            "sell",
        )
        return redirect("/")
    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol",
            user_id,
        )
        return render_template(
            "sell.html",
            symbols=symbols,
        )
