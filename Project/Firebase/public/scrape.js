var request = require('request');
var cheerio = require('cheerio');
var curl = require('curl');

request('https://www.hanyang.ac.kr/web/www/-249', function (error, response, html) {
  if (!error && response.statusCode == 200) {

    var $ = cheerio.load(html);
    $("div.pop_img").each(function(i, element){
     var meal = $(this).find("img");
     console.log(meal);




   });


  //  var message = mtext;
  //
  //  curl.postJSON('https://donwork-233dd.firebaseio.com/menu.json', {"restaurant1": message}, function(err, response, data){});


  //  var $ = cheerio.load(html);
  //  $("in-box").each(function(i, element){
  //   var meal = $(this).find("li");
  //   //var mtext = meal.attr('alt');
  //   console.log(meal.attr('alt'));
   //
  //   });


  }
});
