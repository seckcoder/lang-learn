

function queryHBase(req, resp) {
  var term = req.term;
  var tablename = "some table";
  var columnfamily = "column family";
  var url = "http://localhost:8080/" + tablename + "/" + encodeURI(term);
  $.ajax({
    url: url,
    type: "GET",
    dataType: "json"
  }).done(function (data) {
    console.log(data);
  }).fail(function (err) {
  });
}
$(document).ready(function () {
  $("#searchBox").autocomplete({source: queryHBase(), minLength:4});
});
