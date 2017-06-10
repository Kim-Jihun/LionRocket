var request = require('request');
var cheerio = require('cheerio');
var curl = require('curl');
var postMenu = "str";
var testString = "strstrstrstr";

request('https://www.hanyang.ac.kr/web/www/-249', function (error, response, html) {
  if (!error && response.statusCode == 200) {

    var $ = cheerio.load(html);

    var postElements = $("pre");
    postElements.each(function() {
    postMenu = $(this).text();

    console.log(postMenu);

    curl.postJSON('https://donwork-233dd.firebaseio.com/menu.json', {"NEW TEST": postMenu}, function(err, response, data){});
    curl.postJSON('https://arduino2-c0fe0.firebaseio.com/menu.json', {"NEW_TEST": postMenu}, function(err, response, data){});

   });

  }
});
