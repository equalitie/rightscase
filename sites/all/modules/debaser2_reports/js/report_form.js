/**
 * @author cormac1
 */

$(document).ready(function(){

	$('.actor').click(actorClicked);
	$('.case').click(function(){
		caseClicked(0);
	});
	$('.violation').click(violationClicked);
	$('#location-radio').click(function(){
		caseClicked(0);
	});
	$('#status-radio').click(function(){
		caseClicked(1);
	});
	$('#edit-case-options').change(function(){
		if($(this).getValue()==1){
			caseClicked(0);
		}
	});
	
	checkInitialConditions();
});

function checkInitialConditions(){
  if($('#edit-case-options').getValue()>0){
    if($('#edit-case-status-options').getValue()>0)
      caseClicked(1);
    else 
      caseClicked(0);
  }else if($('#edit-violation-options').getValue()>0){
  	violationClicked();
  }else{
  	actorClicked();
  }
}

function actorClicked(){
  $('.actor-form').find(':input').attr("disabled", false);
  $('.case-form').find(':input').attr("disabled", true).setValue(0);
  $('.vio-form').find(':input').attr("disabled", true).setValue(0);
  resetHeaders( '.actor-form ');

}

function resetHeaders( clickedClass ){
  $('.stats-header').css( 'background-color', '#ffffff' );
  $('.stats-header').css( 'color', '#63AEE0');
  $( clickedClass ).find('.stats-header').css( 'background-color', '#63AEE0');
  $( clickedClass ).find('.stats-header').css( 'color', '#ffffff');
}
function caseClicked(flag){//edit-case-location-options
	
   resetHeaders( '.case-form' );
	 $('.actor-form').find(':input').attr("disabled", true).setValue(0);
	 $('.case-form').find(':input').attr("disabled", false);
	 $('.vio-form').find(':input').attr("disabled", true).setValue(0);
	 if(flag){
		 $('#edit-case-status-options').attr("disabled", false);
		 $('#edit-case-location-options').attr("disabled", true).setValue(0);
		 $('#status-radio').attr('checked', true);
	 }else{
		 $('#edit-case-location-options').attr("disabled", false);
		 $('#edit-case-status-options').attr("disabled", true).setValue(0);
		 $('#location-radio').attr('checked', true);
	 }
	 
	 
}

function violationClicked(){//edit-violation-location-options
  resetHeaders( '.vio-form' );
  $('.actor-form').find(':input').attr("disabled", true).setValue(0);
  $('.vio-form').find(':input').attr("disabled", false);
  $('.case-form').find(':input').attr("disabled", true).setValue(0);
}
