from http.server import HTTPServer, BaseHTTPRequestHandler
import urllib.parse
import uuid

sessions={}

loginpage="""
<html>
<body>
<h2>Login</h2>
<form method="POST" action="/login">
Username: <input name="username"><br>
Password: <input name="password"><br>
<input type="submit" value="Login">
</form>
</body>
</html>
"""

home_page = """
<html>
<body>
<h1>Home Page</h1>
<a href="/login">Login</a>
</body>
</html>
"""

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/":
            self.send_response(200)
            self.end_headers()
            self.wfile.write(home_page.encode())
        elif self.path == "/login":
            self.send_response(200)
            self.end_headers()
            self.wfile.write(loginpage.encode())

        elif self.path == "/dashboard":

            cookies = self.headers.get("Cookie")

            if cookies and "session_id=" in cookies:

                session_id = cookies.split("session_id=")[1]

                if session_id in sessions:
                    username = sessions[session_id]

                    response = f"""
                    <html>
                    <body>
                    <h1>Welcome {username}</h1>
                    <a href="/logout">Logout</a>
                    </body>
                    </html>
                    """

                    self.send_response(200)
                    self.end_headers()
                    self.wfile.write(response.encode())
                    return

            self.send_response(401)
            self.end_headers()
            self.wfile.write(b"Unauthorized. Please login.")

        elif self.path == "/logout":

            self.send_response(200)
            self.send_header("Set-Cookie", "session_id=deleted")
            self.end_headers()

            self.wfile.write(b"Logged out")

        else:
            self.send_response(404)
            self.end_headers()

    # -------- POST REQUESTS --------

    def do_POST(self):

        if self.path == "/login":

            length = int(self.headers.get("Content-Length"))
            body = self.rfile.read(length).decode()

            data = urllib.parse.parse_qs(body)

            username = data.get("username")[0]
            password = data.get("password")[0]

            if username == "admin" and password == "123":

                session_id = str(uuid.uuid4())
                sessions[session_id] = username

                self.send_response(200)

                self.send_header("Set-Cookie", f"session_id={session_id}")

                self.end_headers()

                self.wfile.write(b"Login successful. Go to /dashboard")

            else:

                self.send_response(401)
                self.end_headers()
                self.wfile.write(b"Invalid credentials")

server = HTTPServer(("localhost", 8000), MyHandler)

print("Server running at http://localhost:8000")

server.serve_forever()