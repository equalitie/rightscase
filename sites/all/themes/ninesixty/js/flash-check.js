$(document).ready(function(){
  
// Globals
// Major version of Flash required
var requiredMajorVersion = 10;
// Minor version of Flash required
var requiredMinorVersion = 0;
// Minor version of Flash required
var requiredRevision = 0;
// Version check based upon the values entered above in "Globals"
var hasReqestedVersion = DetectFlashVer(requiredMajorVersion, requiredMinorVersion, requiredRevision);

// Check to see if the version meets the requirements for playback
if (hasReqestedVersion) {
} else {  // flash is too old or we can't detect the plugin
	var alternateContent = '<span>'+Drupal.t('You have an outdated version of Adobe Flash player. Please ')+'<a href=http://www.adobe.com/go/getflash/ >'+Drupal.t('Click here')+'</a>'+ Drupal.t(' to install the latest version')+'</span>';
   $('#flash-detect').prepend(alternateContent).show();
}  
  
  
  
});