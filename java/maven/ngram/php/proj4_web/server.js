var express = require("express"),
    app = express(),
    http = require("http").createServer(app);

process.chdir(__dirname);

app.use(express.static("public", __dirname + "/public"));

app.use(express.bodyParser());

app.get("/", function (req, res) {
  res.sendfile("index.html");
});

app.set("ipaddr", "0.0.0.0");
app.set("port", "8080");

function start() {
    http.listen(app.get("port"), app.get("ipaddr"), function () {
        console.log("Server up and running. Go to http://" + app.get("ipaddr") + ":" + app.get("port"));
    });
};

start()
