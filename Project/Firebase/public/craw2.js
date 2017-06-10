var request = require('request');
var cheerio = require('cheerio');
var curl = require('curl');
var postMenu = "str";
var testString = "strstrstrstr";

request('http://www.hanyang.ac.kr/web/www/-249', function (error, response, html) {
  if (!error && response.statusCode == 200) {

    var $ = cheerio.load(html);

    var postElements = $("div.pop_img");
    postElements.each(function() {
    postMenu = $(this).find("img").attr("alt");

    console.log(postMenu);

    curl.postJSON('https://donwork-233dd.firebaseio.com/menu.json', {"NEW TEST": postMenu}, function(err, response, data){});

   });

  }
});


document.write("<" + "h1" + ">" + testString + "</h1" + ">");
document.write("<" + "h1" + ">" + postMenu + "</h1" + ">");
