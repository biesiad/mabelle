var express = require('express');
var app = express();

app.set('port', (process.env.PORT || 5000));
app.use(express.static(__dirname + '/public'));

var state = 0
app.get('/', function(request, response) {
  response.send("state:" + state.toString());
  state = 0
});

app.post('/', function(request, response) {
  state = 1
  response.send("state:" + state.toString());
});

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});
