var ss = SpreadsheetApp.openById('1crK2RQrHN4N_V8ItpnYmAjH4KRlxCTrw2D4OEptcNOg');
var sheet = ss.getSheetByName('Sheet1');


function doGet(e){
  //----------------------------------------------------------------------------------
  //write_google_sheet() function in esp32 sketch, is send data to this code block
  //----------------------------------------------------------------------------------
  //get gps data from ESP32
  if (e.parameter == 'undefined') {
    return ContentService.createTextOutput("Received data is undefined");
  }
  //----------------------------------------------------------------------------------
  var dateTime = new Date();
  dist    = e.parameters.dist;
  tmp   = e.parameters.tmp;
  
  //Logger.log('latitude=' + latitude);
  //----------------------------------------------------------------------------------
  var nextRow = sheet.getLastRow() + 1;
  sheet.getRange("A" + nextRow).setValue(dateTime);
  sheet.getRange("B" + nextRow).setValue(dist);
  sheet.getRange("C" + nextRow).setValue(tmp);
  //----------------------------------------------------------------------------------

  //returns response back to ESP32
  return ContentService.createTextOutput("Status Updated in Google Sheet");
  //----------------------------------------------------------------------------------
}