                  let indx = 0;  // used to keep track of all distances

                  /* Function to grab and update the distance every second */
                  let x = setInterval(function() {loadTime("distance.txt",updateTime)}, 1000);
                  function loadTime(url, callback){
                      let xhttp_time = new XMLHttpRequest();
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
                         ++indx;   // increase on each new distance received
                         let timeObj = JSON.parse(this.responseText);
                         document.getElementById("dist").innerHTML = timeObj.distance;
                         let x = document.getElementById("close-text");
                         let dist = parseInt(timeObj.distance, 10);
                            if (dist <= 12) {
                                x.style.color = "red";
                                x.style.display = "inline-block";
                            } else {
                                x.style.display = "none";
                            }
                         // add the new distance to the'all-dists-div' div tag
                         for (let i = 0; i < indx; ++i) {
                                  let para = document.createElement("h3");
                                  let node = document.createTextNode("Distance #" + indx + " = " + timeObj.distance + " inches");
                                  para.appendChild(node);
                                  let element = document.getElementById("all-dists-div");
                                  element.appendChild(para);
                         }
                  }


                  /* Toggle between hiding and showing all distances */
                  function showAllDistances() {
                        let x = document.getElementById("all-dists-div");
                          if (x.style.display === "none") {
                            x.style.display = "block";
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
                          let allDistObj = JSON.parse(this.responseText);

                          // update this to a nice for loop
                          // been having some trouble
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
