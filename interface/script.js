$( document ).ready(function(){

    // Device
    var address = "172.30.0.185";
    var device = new Device(address);w
    console.log(device);

    // Buttons
    $('#forward').mousedown(function() {
      device.callFunction("forward");
    });
    $('#forward').mouseup(function() {
      device.callFunction("stop");
    });

    $('#right').mousedown(function() {
      device.callFunction("right");
    });
    $('#right').mouseup(function() {
      device.callFunction("stop");
    });

    $('#left').mousedown(function() {
      device.callFunction("left");
    });
    $('#left').mouseup(function() {
      device.callFunction("stop");
    });

    $('#backward').mousedown(function() {
      device.callFunction("backward");
    });
    $('#backward').mouseup(function() {
      device.callFunction("stop");
    });

    $('#dance').mousedown(function() {
      device.callFunction("dance");
    });
   // $('#dance').mouseup(function() {
    //  device.callFunction("stop");
    //});
    });


