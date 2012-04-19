/**
 * @author cormac1
 */





var select_options = {"0":"Age of Victim", 
					  "1":"Location of Violation", 
					  "2":"Gender of Victim ", 
					  "3":"Violation Type",  	  
					  "4":"Ethnicity of Victim", 
					  "5":"Reason for Intervention", 
					  "6":"International Legislation", 
					  "7":"Assigned Staff"};
  
$(document).ready(function(){
	
	updateSelectBox(true);
    $("#edit-primary-field-type").change(function(){
       updateSelectBox(false);
    });//
    $("#edit-secondary-field-type").change(function(){
		//alert($(this).val());
       $('#previous').setValue($(this).val());
    });//
    init();
    
});// end document ready

function updateSelectBox(initFlag){
	var selected = $("#edit-primary-field-type").val();
	addValues("#edit-secondary-field-type", selected, initFlag);
}

function init(){
	var prev = $('#previous').getValue();
	 $("#edit-secondary-field-type").setValue($('#previous').getValue());
	// alert($('#edit-primary-field-type').getValue());
	 if (!$('#edit-primary-field-type').getValue() == 1) {
	 	$('#edit-location-wrapper').hide('fast');
	 }
	 if($('#previous').getValue())return true;
}


function addValues(identifier, val, initFlag){
	var secVal = 2;
	switch (val) {
            case '0'://Age
				$("#edit-secondary-field-type").removeOption(/./);
                $(identifier).addOption("2", "Gender of Victim");
				$(identifier).addOption("4", "Ethnicity of Victim");
				$('#edit-location-wrapper').hide('fast');
				$(identifier).setValue(2);
                break;
			case '1':// Location
			
				$(identifier).removeOption(/./);
                $(identifier).addOption("2", "Gender of Victim");
				$(identifier).addOption("4", "Ethnicity of Victim");
				$(identifier).setValue(2);
				
				break;
			case '2'://Gender
				$(identifier).removeOption(/./);
				$(identifier).addOption("4", "Ethnicity of Victim");
				secVal = 4;
				break;
			case '3'://Violation Type
				$(identifier).removeOption(/./);
                $(identifier).addOption("2", "Gender of Victim");
				$(identifier).addOption("4", "Ethnicity of Victim");
				$(identifier).addOption("5", "Reason for Intervention");
				$(identifier).setValue(2);
				break;
			case '4':// Date of violation
				$(identifier).removeOption(/./);
                $(identifier).addOption("2", "Gender of Victim");
				$(identifier).addOption("3", "Violation Type");
				$(identifier).setValue(2);
				break;
			case '5'://Case Status
				$(identifier).removeOption(/./);
				$(identifier).addOption("3", "Violation Type");
                $(identifier).addOption("6", "International Legislation");
				$(identifier).addOption("7", "Assigned Staff");
				$(identifier).setValue(3);
				secVal = 3;
				break;
			
			
        }// end switch
		//update hidden form value
		if(!initFlag)$('#previous').setValue(secVal);
		// show/hide location box
		if(val==1) $('#edit-location-wrapper').show('fast');
		else $('#edit-location-wrapper').hide('fast');
}
*/
