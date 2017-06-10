curl = require('curl');
  // curl('https://donwork-233dd.firebaseio.com/', {VERBOSE: 1, RAW: 1}, function(err) {
  //   console.info(this);
  // });

data = {VERBOSE: 1, RAW: 1};

  curl.postJSON('https://donwork-233dd.firebaseio.com/', {"key": "string"}, function(err, response, data){});
