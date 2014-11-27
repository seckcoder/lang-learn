var express = require("express");
var app = express();
var http = require("http").Server(app);
var io = require('socket.io')(http);


app.use(express.static("public", __dirname + "/public"));
app.use(express.bodyParser());

app.get("/", function (req, res) {
    res.sendfile('template.html');
});

http.listen(3000, function () {
    console.log('on 3000');
});
