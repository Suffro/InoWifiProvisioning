
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
      // Send the Wi-Fi credentials page to the client
      client.println("<html>");
      client.println("<head>");
      client.println("<title>Enter Wi-Fi Credentials</title>");
      client.println("<style>");
      client.println("body{font-family:\"Helvetica\",sans-serif;color:#333;background-color:#fff;padding:20px}h2{width:100%;text-align: center;font-size:24px;font-weight:bold;color:#004080;margin-bottom:1rem;margin-top:50px;}form{display:flex;flex-direction:column;align-items:flex-start;width:300px;margin:0 auto;padding:20px;background-color:rgba(0,128,128,0.1);border-radius:5px}input[type=\"text\"],input[type=\"password\"]{font-size:1rem;padding:0.5rem;border:2px solid #004080;border-radius:4px;margin-bottom:1rem;width:100%}input[type=\"submit\"]{font-size:1rem;padding:0.5rem 1rem;background-color:#004080;color:#fff;border:none;border-radius:4px;cursor:pointer;transition:all 0.3s ease}input[type=\"submit\"]:hover{background-color:#002233}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<h2>Enter Wi-Fi Credentials</h2>");
      client.println("<form method='POST' action='/save'>");
      client.println("SSID: <input type='text' name='ssid'><br>");
      client.println("Password: <input type='password' name='pass'><br>");
      client.println("<input type='submit' value='Save'>");
      client.println("</form>");
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
      client.println("<style>");
      client.println("body{font-family:\"Helvetica\",sans-serif;color:#333;background-color:#fff;padding:20px}h2{width:100%;font-size:24px;font-weight:bold;color:#004080;margin-bottom:1rem;margin-top:50px;}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<h2>Wi-Fi Credentials Saved!</h2>");
      client.println("<p>The device will now try to connect to Wi-Fi using the saved credentials. Please wait a moment.</p>");
      client.println("</p>");
      client.println("</body>");
      client.println("</html>");

      delay(100);

      connectWifi();
    }
    // If the request is for any other page, send a 404 error
    else {
      client.println("HTTP/1.1 404 Not Found");
      client.println("Content-Type: text/html");
      client.println();
      client.println("<html>");
      client.println("<head>");
      client.println("<style>");
      client.println("body{font-family:\"Helvetica\",sans-serif;color:#333;background-color:#fff;padding:20px}h1{width:100%;font-size:36px;font-weight:bold;color:#004080;margin-bottom:1rem;margin-top:50px;}");
      client.println("</style>");
      client.println("</head>");
      client.println("<body>");
      client.println("<h1>404 Not Found</h1>");
      client.println("<p>The requested page could not be found.</p>");
      client.println("</body>");
      client.println("</html>");
    }

    // Disconnect from the client
    client.stop();
  }
}
