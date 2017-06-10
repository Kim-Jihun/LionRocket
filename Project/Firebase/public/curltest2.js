app.get("/add/prospect/", (req,res) => {
    var firstName = "first";
    var lastName = "last";
    var formData = {
        first_name: firstName,
        last_name: lastName
    }
    var url = "https://donwork-233dd.firebaseio.com/";
    var options = {
        method: "POST",
        url:url,
        data: formData,
        json:true,
        headers: {
            "Authorization" : "Basic " + new Buffer(api_key + ":").toString("base64"),
            "On-Behalf-Of": user_id,
            'Content-Type': 'application/json',
        }
    }
    request(options, (error, response, body) => {
        console.log(error);
        res.json(response);
    })
})
