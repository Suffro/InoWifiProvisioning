
WiFiServer server(80);   // create a server object on port 80
WiFiClient client;       // create a client object


void connectWifi(){
    if(ssid[0]=='\0' || pass[0]=='\0') clearCredentials();

    // Connect to Wi-Fi using the saved credentials
    WiFi.begin(ssid, pass);

    // Wait for Wi-Fi to connect
    Serial.println();
    Serial.println("Attempting to connect to network:");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("PASS: ");
    Serial.println(pass);
    Serial.println();

    Serial.print("Connecting to Wi-Fi.");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts<=30) {
      delay(1000);
      attempts++;
      Serial.print(".");
    }
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println();
      Serial.println("Failed to connect to the network.");
      clearCredentials();
    };
    Serial.println("");
    Serial.print("Connected to Wi-Fi with SSID ");
    Serial.println(ssid);

    storeCredentials();
}

void initProvisioningServer(){
  Serial.println("Checking credentials...");
  if(!credentialsSaved()){
    Serial.println("No credentials retreived, starting server.");
    // Set up soft AP with a custom SSID and password
    WiFi.beginAP("arduino", "arduino123");

    // Print the IP address of the access point
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up the web server
    server.begin();

    // print where to go in a browser:
    Serial.print("To see this page in action, open a browser to http://");
    Serial.print(WiFi.localIP());
    Serial.println("/wifi");
  } else {
    retreiveCredentials();
    Serial.println("Credentials retreived.");
    connectWifi();
  }
}

void handleProvisioningServer(){
  // Check if a client has connected
  client = server.available();

  if (client) {
    // Read the request sent by the client
    String request = client.readStringUntil('\r');
    client.flush();

    // Send a response to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();

    // Check if the request is for the Wi-Fi credentials page
    if (request.indexOf("/wifi") != -1) {
      // Send the Wi-Fi credentials page to the client<meta name='viewport' content='width=device-width,initial-scale=1'>
      client.println("<html>");
      client.println("<head>");
      client.println("<meta charset='UTF-8'>");
      client.println("<meta name='viewport' content='width=device-width,initial-scale=1'>");
      // client.println("<link rel='icon' type='image/x-icon' href='https://www.arduino.cc/favicon.ico'>");
      client.println("<title>Connect Wifi</title>");
      client.println("<style>");
      client.println("body{font-family:Helvetica,sans-serif;background-color:#fff; padding:8px;}.container{display:flex;flex-direction:column;justify-content:center;align-items:center;height:100vh}.logo{margin-bottom:1.5rem}.title{font-weight:700;font-size:2rem;margin-bottom:1.5rem;text-align:center;color:#212121}.form{background-color:#fff;padding:2rem;box-shadow:0 1px 2px rgba(0,0,0,.1);border-radius:.5rem;max-width:25rem;width:100%}.input{display:block;width:100%;padding:.75rem;margin-top:.5rem;border-radius:.25rem;border:1px solid #cbd5e0;background-color:#f3f4f6;color:#1f2937;font-size:1rem;font-weight:400;line-height:1.5;transition:border-color .15s ease-in-out,box-shadow .15s ease-in-out}.input:focus{outline:0;border-color:#f59e0b;box-shadow:0 0 0 2px #fde68a}.label{display:block;font-size:.875rem;font-weight:600;line-height:1.5;margin-bottom:.5rem;color:#374151}.button{display:flex;justify-content:center;align-items:center;background-color:#00979C;color:#fff;font-weight:600;font-size:1rem;border-radius:.25rem;padding:.5rem 1rem;transition:background-color .15s ease-in-out;margin-top:1rem;border-style:none}.button:hover{background-color:#96D9D9}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<div class='container'>");
      // client.println("<img class='logo' src='https://www.arduino.cc/favicon.ico' alt='Arduino logo'>");
      client.println("<h2 class='title'>Enter Wifi Credentials</h2><div class='form'><form action='/save' method='POST'><label for='ssid' class='label'>Network name</label><input id='ssid' name='ssid' type='text' required class='input' placeholder='Enter your network name'><br><label for='pass' class='label'>Passowrd</label><input id='pass' name='pass' type='password' class='input' placeholder='Enter your network password'><button class='button'>Save and Connect</button></form></div>");
      client.println("</div>");
      client.println("</body>");
      client.println("</html>");
    }
    // Check if the request is for the save credentials page
    else if (request.indexOf("/save") != -1) {
      // Read the Wi-Fi credentials from the request
      String ssidParam = "";
      String passParam = "";
      if (client.available()) {
        String line = client.readStringUntil('\r');
        while (line.indexOf("ssid=") == -1 && line.indexOf("pass=") == -1) {
          line = client.readStringUntil('\r');
        }
        if (line.indexOf("ssid=") != -1) {
          int ssidStart = line.indexOf("ssid=") + 5;
          int ssidEnd = line.indexOf("&", ssidStart); // Find the next "&" character
          ssidParam = line.substring(ssidStart, ssidEnd);
          ssidParam.replace("+", " ");
          ssidParam.trim();
        }
        if (line.indexOf("pass=") != -1) {
          passParam = line.substring(line.indexOf("pass=") + 5);
          passParam.trim();
        }
      }

      // Save the Wi-Fi credentials to the buffer
      ssidParam.toCharArray(ssid, 32);
      passParam.toCharArray(pass, 64);

      // Send a response to the client
      client.println("<html>");
      client.println("<head>");
      client.println("<meta charset='UTF-8'>");
      client.println("<meta name='viewport' content='width=device-width,initial-scale=1'>");
      // client.println("<link rel='icon' type='image/x-icon' href='https://www.arduino.cc/favicon.ico'>");
      client.println("<title>Connect Wifi</title>");
      client.println("<style>");
      client.println("body{font-family:Helvetica,sans-serif;background-color:#fff; padding:8px;}.container{display:flex;flex-direction:column;justify-content:center;align-items:center;height:100vh}.logo{margin-bottom:1.5rem}.title{font-weight:700;font-size:2rem;margin-bottom:1.5rem;text-align:center;color:#212121}.form{background-color:#fff;padding:2rem;box-shadow:0 1px 2px rgba(0,0,0,.1);border-radius:.5rem;max-width:25rem;width:100%}.input{display:block;width:100%;padding:.75rem;margin-top:.5rem;border-radius:.25rem;border:1px solid #cbd5e0;background-color:#f3f4f6;color:#1f2937;font-size:1rem;font-weight:400;line-height:1.5;transition:border-color .15s ease-in-out,box-shadow .15s ease-in-out}.input:focus{outline:0;border-color:#f59e0b;box-shadow:0 0 0 2px #fde68a}.label{display:block;font-size:.875rem;font-weight:600;line-height:1.5;margin-bottom:.5rem;color:#374151}.button{display:flex;justify-content:center;align-items:center;background-color:#00979C;color:#fff;font-weight:600;font-size:1rem;border-radius:.25rem;padding:.5rem 1rem;transition:background-color .15s ease-in-out;margin-top:1rem;border-style:none}.button:hover{background-color:#96D9D9}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<div class='container'>");
      // client.println("<img class='logo' src='https://www.arduino.cc/favicon.ico' alt='Arduino logo'>");
      client.println("<h2 class='title'>Credentials saved</h2>");
      client.println("<p>Credentials saved, the board will now try to connect.</p>");
      client.println("</div>");
      client.println("</body>");
      client.println("</html>");

      delay(500);

      connectWifi();
    }
    // If the request is for any other page, send a 404 error
    else {
      client.println("HTTP/1.1 404 Not Found");
      client.println("Content-Type: text/html");
      client.println();
      client.println("<html>");
      client.println("<head>");
      client.println("<meta charset='UTF-8'>");
      client.println("<meta name='viewport' content='width=device-width,initial-scale=1'>");
      // client.println("<link rel='icon' type='image/x-icon' href='https://www.arduino.cc/favicon.ico'>");
      client.println("<title>Connect Wifi</title>");
      client.println("<style>");
      client.println("body{font-family:Helvetica,sans-serif;background-color:#fff; padding:8px;}.container{display:flex;flex-direction:column;justify-content:center;align-items:center;height:100vh}.logo{margin-bottom:1.5rem}.title{font-weight:700;font-size:2rem;margin-bottom:1.5rem;text-align:center;color:#212121}.form{background-color:#fff;padding:2rem;box-shadow:0 1px 2px rgba(0,0,0,.1);border-radius:.5rem;max-width:25rem;width:100%}.input{display:block;width:100%;padding:.75rem;margin-top:.5rem;border-radius:.25rem;border:1px solid #cbd5e0;background-color:#f3f4f6;color:#1f2937;font-size:1rem;font-weight:400;line-height:1.5;transition:border-color .15s ease-in-out,box-shadow .15s ease-in-out}.input:focus{outline:0;border-color:#f59e0b;box-shadow:0 0 0 2px #fde68a}.label{display:block;font-size:.875rem;font-weight:600;line-height:1.5;margin-bottom:.5rem;color:#374151}.button{display:flex;justify-content:center;align-items:center;background-color:#00979C;color:#fff;font-weight:600;font-size:1rem;border-radius:.25rem;padding:.5rem 1rem;transition:background-color .15s ease-in-out;margin-top:1rem;border-style:none}.button:hover{background-color:#96D9D9}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<div class='container'>");
      // client.println("<img class='logo' src='https://www.arduino.cc/favicon.ico' alt='Arduino logo'>");
      client.println("<h2 class='title'>404</h2>");
      client.println("<p>Sorry, the requested resource was not found.</p>");
      client.println("</div>");
      client.println("</body>");
      client.println("</html>");

    }
    
    delay(500);
    // Disconnect from the client
    client.stop();
  }
}
