var express = require('express');
var app = express();

app.set('port', (process.env.PORT || 5000));
app.use(express.static(__dirname + '/public'));

app.get('/status', function(request, response) {
  response.send(Date() + ". It's working (state:" + state.toString() + ").");
});

var state = 0
app.get('/bell', function(request, response) {
  response.send("state:" + state.toString());
  state = 0
});

app.post('/bell', function(request, response) {
  state = 1
  response.send("state:" + state.toString());
});

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});
