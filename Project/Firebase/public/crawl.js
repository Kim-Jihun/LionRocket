var request = require('request');
var cheerio = require('cheerio');


request('http://www.hanyang.ac.kr/web/www/-249', function (error, response, html) {
  if (!error && response.statusCode == 200) {

    var $ = cheerio.load(html);
    $("div.pop_img").each(function(i, element){
    meal = $(this);
    var mtext = meal.attr('alt');

     console.log(meal);





   });

  }
});
