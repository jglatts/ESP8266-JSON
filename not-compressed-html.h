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
