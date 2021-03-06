
    /*
     * HTML Header file for nodemcu ajax sketch
     * Author: John Glatts
     * Date: 4/8/19
     * Use stats feature from ESP-DASH to display better stats
     *
     *    ToDo:
     *        - test if the one-time JSON 'GET' will work for about -- than transfer to the stats page
     *        - Add more fn's() and var's to the .h file
     *
     */


    const char page[] = R"=====(
               <head>
               <title>JDG SERVER</title>
               <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
               </head>
               <body>
               <h1 class="name">JDG ESP SERVER</h1>
                <div class="rc_nav" id="centered_nav">
                <a href="/">Home</a>
                <a href="Stats">Board Stats</a>
                <a href="About">About</a>
                <a href="Reboot">Reboot</a>
                <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
                </div>
               <h1 class="content">Sensor to Node MCU Web Server</h1>
               <div id = "all-buttons">
               <button class="content-buttons" id="button1"><a href="Time">Time It</a></button>
               <button class="content-buttons"><a href="MotorOn">Motor On</a></button>
               <button class="content-buttons"><a href="Pixel">Control Pixel</a></button>
               <button class="content-buttons"><a href="RFID">RFID Access</a></button>
               </div>
               <div id="user-info">
               <h1 style="display:inline-block">Current User: </h1>
               <h1 style="display:inline-block" id="current_user"></h1>
               <br>
               <h1 style="display:inline-block">Card ID: </h1>
               <h1 style="display:inline-block" id="current_id"></h1>
               <br>
               <h1 style="display:inline-block">Number of System Check-Ins: </h1>
               <h1 style="display:inline-block" id="number_check_ins"></h1>
               <br>
               <div id="toggleview">
               <button class="content-buttons" onclick="pixelControl('PixelControl.txt', lightUpPixel)">Light Up Pixel</h1>
               <button class="content-buttons" onclick="pixelControl('RFIDMotor.txt', lightUpPixel)">Cycle Motor</h1>
               <button class="content-buttons"><a href="GetDistance">Check Distance</a></h1>
               </div>
               </div>
               </body>
                <script>
                      var x = setInterval(function() {loadData('data.txt',updateData)}, 1000)
                      function loadData(url, callback){
                        var xhttp = new XMLHttpRequest()
                        xhttp.onreadystatechange = function(){
                        if(this.readyState == 4 && this.status == 200){
                            callback.apply(xhttp)
                          }
                        };
                        xhttp.open("GET", url, true)
                        xhttp.send()
                      }
                      function updateData(){
                        console.log(this.responseText)
                        var userObj = JSON.parse(this.responseText)
                        document.getElementById("current_user").innerHTML = userObj.current_user
                        document.getElementById("current_id").innerHTML = userObj.current_id
                        document.getElementById("number_check_ins").innerHTML = userObj.number_check_ins
                        var check_user = document.getElementById("current_user")
                        var hide = document.getElementById("toggleview")
                        if (check_user.innerHTML === "User Unknown") {
                            hide.style.display = "none"
                          } else {
                            hide.style.display = "inline-block"
                          }
                      }
                      function pixelControl(pix_url, pix_callback) {
                        var xhttp_pix = new XMLHttpRequest()
                        xhttp_pix.onreadystatechange = function(){
                        if(this.readyState == 4 && this.status == 200){
                            pix_callback.apply(xhttp_pix)
                          }
                        };
                        xhttp_pix.open("GET", pix_url, true)
                        xhttp_pix.send()
                      }
                      function lightUpPixel() {
                        console.log("Test")
                      }
                      function myFunction() {
                        var x = document.getElementById("centered_nav")
                        if (x.className === "rc_nav") {
                            x.className += " responsive"
                        } else {
                            x.className = "rc_nav"
                        }
                      }
                  </script>
                  <style>
                    body {
                      background-color: whitesmoke;
                      font-family: 'Roboto', sans-serif;
                    }
                    .name {
                      size: 4em;
                      text-align: center;
                    }
                    a {
                      text-decoration: none;
                    }
                    .content {
                      text-align: center;
                    }
                    #all-buttons {
                        text-align: center;
                    }
                    #user-info {
                        margin-top: 2em;
                        text-align: center;
                    }
                    .content-buttons {
                      margin-top: 1em;
                      margin-right: 14px;
                      padding: 20px;
                      background-color: Gainsboro;
                      font-size: 2em;
                      text-align: center;
                     }
                    .rc_nav {
                      overflow: hidden;
                      background-color: #363841;
                      text-align: center;
                      z-index: 6;
                    }

                    .rc_nav a {
                     display: inline-block;
                     margin-right: -4px;  /* inline-block gap fix */
                     color: #fff;
                     padding: 22px 22px;
                     text-decoration: none;
                     font-family: Poppins;
                     font-size: 18px;
                     -webkit-transition: background 0.3s linear;
                     -moz-transition: background 0.3s linear;
                     -ms-transition: background 0.3s linear;
                     -o-transition: background 0.3s linear;
                     transition: background 0.3s linear;
                     z-index: 9;
                    }

                    .rc_nav a:hover {
                      background-color: #575b69;
                      color: #bdfe0e2;
                    }

                    .rc_nav .icon {
                      display: none;
                    }

                    .rc_content {
                      text-align: center;
                      padding-left:14px;
                      font-family: Poppins;
                      margin-top: 100px;
                      color: #8e909b;
                    }


                    @media screen and (max-width: 820px) {
                      .rc_nav a {display: none;}
                      .rc_nav a.icon {
                        float: right;
                        display: block;
                        width: 60px;
                      }
                    }

                    @media screen and (max-width: 820px) {
                      .rc_nav.responsive {position: relative; top: 73px;}
                      .rc_nav.responsive .icon {
                        position: fixed;
                        right: 0;
                        top: 0;
                      }
                      .rc_nav.responsive a {
                        float: none;
                        display: block;
                        text-align: center;
                      }
                    }
                  </style>
          )=====";
    // elapsed time page
    const char time_page[] = R"=====(
              <head>
               <meta charset="UTF-8">
               <title>JDG SERVER</title>
               <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
              </head>
              <h1 class="name">JDG ESP SERVER</h1>
              <div class="rc_nav" id="centered_nav">
                <a href="/">Home</a>
                <a href="Stats">Board Stats</a>
                <a href="About">About</a>
                <a href="Reboot">Reboot</a>
                <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
              </div>
              <div class="time-content">
              <h1>Sensor to Node MCU Web Server</h1>
              <h1 style="display:inline;">Elapsed Time: </h1><h1 id="mins" style="display:inline;"></h1><h1 style="display:inline;"> mins </h1>
              <h1 style="display:inline;"> and </h1><h1 id="secs" style="display:inline;"></h1>
              <h1 style="display:inline;"> secs. </h1>
              </div>
                <script>
                  var x = setInterval(function() {loadTime("time.txt",updateTime)}, 1000)
                  function loadTime(url, callback){
                      var xhttp_time = new XMLHttpRequest()
                      xhttp_time.onreadystatechange = function(){
                      if(this.readyState == 4 && this.status == 200){
                          callback.apply(xhttp_time)
                      }
                  };
                  xhttp_time.open("GET", url, true)
                  xhttp_time.send()
                  }
                  function updateTime(){
                          console.log(this.responseText)
                          var timeObj = JSON.parse(this.responseText)
                          document.getElementById("mins").innerHTML = timeObj.mins
                          document.getElementById("secs").innerHTML = timeObj.secs
                  }
                  function myFunction() {
                        var x = document.getElementById("centered_nav");
                        if (x.className === "rc_nav") {
                            x.className += " responsive";
                        } else {
                            x.className = "rc_nav";
                        }
                  }
              </script>
               <style>
                    body {
                      background-color: whitesmoke;
                      font-family: 'Roboto', sans-serif;
                    }
                    .name {
                      size: 4em;
                      text-align: center;
                    }
                    .time-content {
                      text-align: center;
                    }
                    .content {
                      text-align: center;
                    }
                    .rc_nav {
                      overflow: hidden;
                      background-color: #363841;
                      text-align: center;
                      z-index: 6;
                    }

                    .rc_nav a {
                     display: inline-block;
                     margin-right: -4px;  /* inline-block gap fix */
                     color: #fff;
                     padding: 22px 22px;
                     text-decoration: none;
                     font-family: Poppins;
                     font-size: 18px;
                     -webkit-transition: background 0.3s linear;
                     -moz-transition: background 0.3s linear;
                     -ms-transition: background 0.3s linear;
                     -o-transition: background 0.3s linear;
                     transition: background 0.3s linear;
                     z-index: 9;
                    }

                    .rc_nav a:hover {
                      background-color: #575b69;
                      color: #bdfe0e2;
                    }

                    .rc_nav .icon {
                      display: none;
                    }

                    .rc_content {
                      text-align: center;
                      padding-left:14px;
                      font-family: Poppins;
                      margin-top: 100px;
                      color: #8e909b;
                    }


                    @media screen and (max-width: 820px) {
                      .rc_nav a {display: none;}
                      .rc_nav a.icon {
                        float: right;
                        display: block;
                        width: 60px;
                      }
                    }

                    @media screen and (max-width: 820px) {
                      .rc_nav.responsive {position: relative; top: 73px;}
                      .rc_nav.responsive .icon {
                        position: fixed;
                        right: 0;
                        top: 0;
                      }
                      .rc_nav.responsive a {
                        float: none;
                        display: block;
                        text-align: center;
                      }
                    }
                </style>
          )=====";
    // stats page
    // loads JSON in intervals, get the fn() to go the page just once
    const char board_stats_page[] = /* R"=====(

                <script>
                      function loadJSON(url, callback){
                        var xhttp = new XMLHttpRequest()
                        xhttp.onreadystatechange = function(){
                        if(this.readyState == 4 && this.status == 200){
                            callback.apply(xhttp)
                          }
                        };
                        xhttp.open("GET", url, true)
                        xhttp.send()
                      }
                      function updateJSON(){
                          console.log(this.responseText)
                          console.log('Test')
                          var statsObj = JSON.parse(this.responseText)
                          document.getElementById("chipID").innerHTML = statsObj.chipID
                          document.getElementById("mac_address").innerHTML = statsObj.mac_address
                          document.getElementById("sketch_hash").innerHTML = statsObj.sketch_hash
                          document.getElementById("wifi_mode").innerHTML = statsObj.wifi_mode
                          document.getElementById("local_ip").innerHTML = statsObj.local_ip
                      }
                      function myFunction() {
                        var x = document.getElementById("centered_nav");
                        if (x.className === "rc_nav") {
                            x.className += " responsive";
                        } else {
                            x.className = "rc_nav";
                        }
                      }
              </script>
              <head>
               <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1.0">
               <title>JDG SERVER</title>
               <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
              </head>
              <body onload="loadJSON('stats.json', updateJSON)">
              <h1 class="name">JDG ESP SERVER</h1>
              <div class="rc_nav" id="centered_nav">
                <a href="/">Home</a>
                <a href="Stats">Board Stats</a>
                <a href="About">About</a>
                <a href="Reboot">Reboot</a>
                <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
              </div>
              <div class="time-content">
              <h2 style="display:inline-block;">Chip ID: </h2>
              <h2 id = "chipID" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">MAC Address: </h2>
              <h2 id = "mac_address" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">Sketch Hash: </h2>
              <h2 id = "sketch_hash" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">WiFi Mode: </h2>
              <h2 id = "wifi_mode" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">Local IP: </h2>
              <h2 id = "local_ip" style="display:inline-block;"></h2></div>
              </body>
               <style>
                    body {
                      background-color: whitesmoke;
                      font-family: 'Roboto', sans-serif;
                    }
                    .name {
                      size: 4em;
                      text-align: center;
                    }
                    .time-content {
                      text-align: center;
                    }
                    .content {
                      text-align: center;
                    }
                    .rc_nav {
                      overflow: hidden;
                      background-color: #363841;
                      text-align: center;
                      z-index: 6;
                    }

                    .rc_nav a {
                     display: inline-block;
                     margin-right: -4px;  // inline-block gap fix
                     color: #fff;
                     padding: 22px 22px;
                     text-decoration: none;
                     font-family: Poppins;
                     font-size: 18px;
                     -webkit-transition: background 0.3s linear;
                     -moz-transition: background 0.3s linear;
                     -ms-transition: background 0.3s linear;
                     -o-transition: background 0.3s linear;
                     transition: background 0.3s linear;
                     z-index: 9;
                    }

                    .rc_nav a:hover {
                      background-color: #575b69;
                      color: #bdfe0e2;
                    }

                    .rc_nav .icon {
                      display: none;
                    }

                    .rc_content {
                      text-align: center;
                      padding-left:14px;
                      font-family: Poppins;
                      margin-top: 100px;
                      color: #8e909b;
                    }


                    @media screen and (max-width: 820px) {
                      .rc_nav a {display: none;}
                      .rc_nav a.icon {
                        float: right;
                        display: block;
                        width: 60px;
                      }
                    }

                    @media screen and (max-width: 820px) {
                      .rc_nav.responsive {position: relative; top: 73px;}
                      .rc_nav.responsive .icon {
                        position: fixed;
                        right: 0;
                        top: 0;
                      }
                      .rc_nav.responsive a {
                        float: none;
                        display: block;
                        text-align: center;
                      }
                    }
                </style>
          )=====" */
            "";
    /* About Page
     *  - The JS works, only loads the JSON one time
     *  - Change some other pages to this JS style
     *
     */
    const char board_about_page[] = /* R"=====(
                <script>
                      function loadJSON(url, callback){
                        var xhttp = new XMLHttpRequest()
                        xhttp.onreadystatechange = function(){
                        if(this.readyState == 4 && this.status == 200){
                            callback.apply(xhttp)
                          }
                        };
                        xhttp.open("GET", url, true)
                        xhttp.send()
                      }
                      function updateJSON(){
                          console.log(this.responseText)
                          console.log('Test')
                          var aboutObj = JSON.parse(this.responseText)
                          document.getElementById("author").innerHTML = aboutObj.author
                          document.getElementById("created").innerHTML = aboutObj.created
                          document.getElementById("brief").innerHTML = aboutObj.brief
                          document.getElementById("version").innerHTML = aboutObj.version
                      }
                      function myFunction() {
                        var x = document.getElementById("centered_nav");
                        if (x.className === "rc_nav") {
                            x.className += " responsive";
                        } else {
                            x.className = "rc_nav";
                        }
                      }
              </script>
              <head>
               <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1.0">
               <title>JDG SERVER</title>
               <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
              </head>
              <body onload="loadJSON('about.json', updateJSON)">
              <h1 class="name">JDG ESP SERVER</h1>
              <div class="rc_nav" id="centered_nav">
                <a href="/">Home</a>
                <a href="Stats">Board Stats</a>
                <a href="About">About</a>
                <a href="Reboot">Reboot</a>
                <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
              </div>
              <div class="time-content">
              <h2 style="display:inline-block;">Author: </h2>
              <h2 id = "author" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">Date Created: </h2>
              <h2 id = "created" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">Program Brief: </h2>
              <h2 id = "brief" style="display:inline-block;"></h2>
              <br>
              <h2 style="display:inline-block;">JDG-ESP Version: </h2>
              <h2 id = "version" style="display:inline-block;"></h2>
              <br>
              </body>
               <style>
                    body {
                      background-color: whitesmoke;
                      font-family: 'Roboto', sans-serif;
                    }
                    .name {
                      size: 4em;
                      text-align: center;
                    }
                    .time-content {
                      text-align: center;
                    }
                    .content {
                      text-align: center;
                    }
                    .rc_nav {
                      overflow: hidden;
                      background-color: #363841;
                      text-align: center;
                      z-index: 6;
                    }

                    .rc_nav a {
                     display: inline-block;
                     margin-right: -4px;  // inline-block gap fix
                     color: #fff;
                     padding: 22px 22px;
                     text-decoration: none;
                     font-family: Poppins;
                     font-size: 18px;
                     -webkit-transition: background 0.3s linear;
                     -moz-transition: background 0.3s linear;
                     -ms-transition: background 0.3s linear;
                     -o-transition: background 0.3s linear;
                     transition: background 0.3s linear;
                     z-index: 9;
                    }

                    .rc_nav a:hover {
                      background-color: #575b69;
                      color: #bdfe0e2;
                    }

                    .rc_nav .icon {
                      display: none;
                    }

                    .rc_content {
                      text-align: center;
                      padding-left:14px;
                      font-family: Poppins;
                      margin-top: 100px;
                      color: #8e909b;
                    }


                    @media screen and (max-width: 820px) {
                      .rc_nav a {display: none;}
                      .rc_nav a.icon {
                        float: right;
                        display: block;
                        width: 60px;
                      }
                    }

                    @media screen and (max-width: 820px) {
                      .rc_nav.responsive {position: relative; top: 73px;}
                      .rc_nav.responsive .icon {
                        position: fixed;
                        right: 0;
                        top: 0;
                      }
                      .rc_nav.responsive a {
                        float: none;
                        display: block;
                        text-align: center;
                      }
                    }
                </style>
          )=====" */
            "";
    /*
     * RFID Module HTML/JS page
     *      - Displays current user and cards that are checked
     * */
    const char rfid_page_html[] = R"=====(
                <script>
                 var x = setInterval(function() {loadTime("distance.txt",updateTime)}, 1000);
                  function loadTime(url, callback){
                      var xhttp_time = new XMLHttpRequest();
                      xhttp_time.onreadystatechange = function(){
                      if(this.readyState == 4 && this.status == 200){
                          callback.apply(xhttp_time)
                      }
                  };
                  xhttp_time.open("GET", url, true);
                  xhttp_time.send()
                  }


                  function updateTime(){
                          console.log(this.responseText);
                          var timeObj = JSON.parse(this.responseText);
                          document.getElementById("dist").innerHTML = timeObj.distance;
                         var x = document.getElementById("close-text");
                         var dist = parseInt(timeObj.distance, 10);
                            if (dist <= 12) {
                                x.style.color = "red";
                                x.style.display = "inline-block";
                            } else {
                                x.style.display = "none";
                            }
                  }


                  function updateAllDistances(url_reset, callback_reset){
                     var xhttp_reset = new XMLHttpRequest();
                     xhttp_reset.onreadystatechange = function(){
                        if(this.readyState == 4 && this.status == 200){
                            callback_reset.apply(xhttp_reset)
                        }
                     };
                        xhttp_reset.open("GET", url_reset, true);
                        xhttp_reset.send()
                  }


                  function updateTxtAllDists(){
                          // working -- but update so a nice for-loop will work
                          console.log(this.responseText);
                          var allDistObj = JSON.parse(this.responseText);
                          document.getElementById("dis1").innerHTML = allDistObj.dis_one;
                          document.getElementById("dis2").innerHTML = allDistObj.dis_two;
                          document.getElementById("dis3").innerHTML = allDistObj.dis_three;
                          document.getElementById("dis4").innerHTML = allDistObj.dis_four;
                          document.getElementById("dis5").innerHTML = allDistObj.dis_five;
                          document.getElementById("dis6").innerHTML = allDistObj.dis_six
                  }


                  function myFunction() {
                        var x = document.getElementById("centered_nav");
                        if (x.className === "rc_nav") {
                            x.className += " responsive";
                        } else {
                            x.className = "rc_nav";
                        }
                  }
               <head>
               <title>JDG SERVER</title>
               <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
               </head>
               <body>
               <h1 class="name">JDG ESP SERVER</h1>
                <div class="rc_nav" id="centered_nav">
                <a href="/">Home</a>
                <a href="Stats">Board Stats</a>
                <a href="About">About</a>
                <a href="Reboot">Reboot</a>
                <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
                </div>
               <div id="rfid-wrapper">
               <h1 class="content">Sensor to Node MCU Web Server</h1>
               <br>
               <h1 class="content" style="display:inline-block;">Current User: </h1>
               <h1 class="content" id="user" style="display:inline-block;"> </h1>
               <br>
               <h1 class="content" style="display:inline-block;">Card ID: </h1>
               <h1 class="content" id="tag_card_id" style="display:inline-block;"> </h1>
               <br>
               <button class="content" id="btn-content" style="display:inline-block;" onclick="resetUID('resetUID.json', resetCardUID)">Reset Card Reader</button>
               </div>
               </body>
                  <style>
                    body {
                      background-color: whitesmoke;
                      font-family: 'Roboto', sans-serif;
                    }
                    #user-title {
                      display: inline-block;
                      text-align: center;
                    }
                    #user {
                      margin-top: 1em;
                      display: inline-block;
                      text-align: center;
                    }
                    .name {
                      size: 4em;
                      text-align: center;
                    }
                    a {
                      text-decoration: none;
                    }
                    .content {
                      text-align: center;
                    }
                    #btn-content {
                      padding: 15px;
                      height: 2em;
                    }
                    #all-buttons {
                        text-align: center;
                    }
                    #rfid-wrapper {
                        text-align: center;
                    }
                    .content-buttons {
                      margin-top: 1em;
                      margin-right: 14px;
                      padding: 20px;
                      background-color: Gainsboro;
                      font-size: 2em;
                      text-align: center;
                     }
                    .rc_nav {
                      overflow: hidden;
                      background-color: #363841;
                      text-align: center;
                      z-index: 6;
                    }

                    .rc_nav a {
                     display: inline-block;
                     margin-right: -4px;  /* inline-block gap fix */
                     color: #fff;
                     padding: 22px 22px;
                     text-decoration: none;
                     font-family: Poppins;
                     font-size: 18px;
                     -webkit-transition: background 0.3s linear;
                     -moz-transition: background 0.3s linear;
                     -ms-transition: background 0.3s linear;
                     -o-transition: background 0.3s linear;
                     transition: background 0.3s linear;
                     z-index: 9;
                    }

                    .rc_nav a:hover {
                      background-color: #575b69;
                      color: #bdfe0e2;
                    }

                    .rc_nav .icon {
                      display: none;
                    }

                    .rc_content {
                      text-align: center;
                      padding-left:14px;
                      font-family: Poppins;
                      margin-top: 100px;
                      color: #8e909b;
                    }


                    @media screen and (max-width: 820px) {
                      .rc_nav a {display: none;}
                      .rc_nav a.icon {
                        float: right;
                        display: block;
                        width: 60px;
                      }
                    }

                    @media screen and (max-width: 820px) {
                      .rc_nav.responsive {position: relative; top: 73px;}
                      .rc_nav.responsive .icon {
                        position: fixed;
                        right: 0;
                        top: 0;
                      }
                      .rc_nav.responsive a {
                        float: none;
                        display: block;
                        text-align: center;
                      }
                    }
                  </style>
          )=====";

    // distance page
    const char distance_page[] = R"=====(
                <script>
                  var x = setInterval(function() {loadTime("distance.txt",updateTime)}, 1000)
                  function loadTime(url, callback){
                      var xhttp_time = new XMLHttpRequest()
                      xhttp_time.onreadystatechange = function(){
                      if(this.readyState == 4 && this.status == 200){
                          callback.apply(xhttp_time)
                      }
                  };
                  xhttp_time.open("GET", url, true)
                  xhttp_time.send()
                  }
                  function updateTime(){
                          console.log(this.responseText)
                          var timeObj = JSON.parse(this.responseText)
                          document.getElementById("dist").innerHTML = timeObj.distance
                         var x = document.getElementById("close-text")
                         var dist = parseInt(timeObj.distance, 10)
                            if (dist <= 12) {
                                x.style.color = "red";
                                x.style.display = "inline-block";
                            } else {
                                x.style.display = "none";
                            }
                  }
                  function updateAllDistances(url_reset, callback_reset){
                     var xhttp_reset = new XMLHttpRequest()
                     xhttp_reset.onreadystatechange = function(){
                        if(this.readyState == 4 && this.status == 200){
                            callback_reset.apply(xhttp_reset)
                        }
                     };
                        xhttp_reset.open("GET", url_reset, true)
                        xhttp_reset.send()
                  }
                  function updateTxtAllDists(){
                          console.log(this.responseText);
                          var allDistObj = JSON.parse(this.responseText);
                          var i;
                          var dis;
                          var index = ["A", "B", "C", "D", "E"];
                          for (i = 0; i < 6; ++i) {
                              var dis = index[i];
                              console.log(this.responseText);
                              var para = document.createElement("p");
                              var node = document.createTextNode(allDistObj.dist_index);
                              para.appendChild(node);
                              var element = document.getElementById("all-dists-div");
                              element.appendChild(para);
                          }
                  }
                  function myFunction() {
                        var x = document.getElementById("centered_nav");
                        if (x.className === "rc_nav") {
                            x.className += " responsive";
                        } else {
                            x.className = "rc_nav";
                        }
                  }
              </script>
              <head>
               <meta charset="UTF-8">
               <title>JDG SERVER</title>
               <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet">
              </head>
              <h1 class="name">JDG ESP SERVER</h1>
              <div class="rc_nav" id="centered_nav">
                <a href="/">Home</a>
                <a href="Stats">Board Stats</a>
                <a href="About">About</a>
                <a href="Reboot">Reboot</a>
                <a href="javascript:void(0);" title="Menu" style="font-size:18px;" class="icon" onclick="myFunction()">&#9776;</a>
              </div>
              <div class="time-content">
              <h1>Sensor to Node MCU Web Server</h1>
              <h1 style="display:inline;">Distance: </h1><h1 id="dist" style="display:inline;"></h1><h1 style="display:inline;"> inches </h1>
              <br>
              <button onclick="updateAllDistances('AllDistances.txt', updateTxtAllDists)">Check All Distances</button>
              <br>
              <h1 id="close-text">HARMFUL OBJECT</h1>
              <br>
              <div id="all-dists-div">
              <p id="all-dists"></p>
              </div>
              </div>
               <style>
                    body {
                      background-color: whitesmoke;
                      font-family: 'Roboto', sans-serif;
                    }
                    .name {
                      size: 4em;
                      text-align: center;
                    }
                    .time-content {
                      text-align: center;
                    }
                    .content {
                      text-align: center;
                    }
                    .rc_nav {
                      overflow: hidden;
                      background-color: #363841;
                      text-align: center;
                      z-index: 6;
                    }

                    .rc_nav a {
                     display: inline-block;
                     margin-right: -4px;  /* inline-block gap fix */
                     color: #fff;
                     padding: 22px 22px;
                     text-decoration: none;
                     font-family: Poppins;
                     font-size: 18px;
                     -webkit-transition: background 0.3s linear;
                     -moz-transition: background 0.3s linear;
                     -ms-transition: background 0.3s linear;
                     -o-transition: background 0.3s linear;
                     transition: background 0.3s linear;
                     z-index: 9;
                    }

                    .rc_nav a:hover {
                      background-color: #575b69;
                      color: #bdfe0e2;
                    }

                    .rc_nav .icon {
                      display: none;
                    }

                    .rc_content {
                      text-align: center;
                      padding-left:14px;
                      font-family: Poppins;
                      margin-top: 100px;
                      color: #8e909b;
                    }


                    @media screen and (max-width: 820px) {
                      .rc_nav a {display: none;}
                      .rc_nav a.icon {
                        float: right;
                        display: block;
                        width: 60px;
                      }
                    }

                    @media screen and (max-width: 820px) {
                      .rc_nav.responsive {position: relative; top: 73px;}
                      .rc_nav.responsive .icon {
                        position: fixed;
                        right: 0;
                        top: 0;
                      }
                      .rc_nav.responsive a {
                        float: none;
                        display: block;
                        text-align: center;
                      }
                    }
                </style>
          )=====";
