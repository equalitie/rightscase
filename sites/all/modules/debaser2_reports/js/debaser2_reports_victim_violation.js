
Drupal.behaviors.correlative_form = function(context){
  updateFormVio();

  $('#edit-violation-victim-options').change( function(){
    updateFormVio();
  });

  $('.victims').click(victimsClicked);
  $('.political_affiliation').click(political_affiliationClicked);
  $('.others-stats').click(others_statsClicked);
  
  checkInitialConditions();
	
};

/**
 *
 */
function checkInitialConditions(){
  if($('#edit-political-affiliation-options').getValue() != 0){
    political_affiliationClicked();
  }else{
    if($('#edit-other-statistics').getValue() != 0){
      others_statsClicked();
  	} else {
  	  victimsClicked();  	
  	}
  }
}

/**
 *
 */
function resetHeaders( clickedClass ){
  $('.stats-header').css( 'background-color', '#ffffff' );
  $('.stats-header').css( 'color', '#63AEE0');
  $( clickedClass ).find('.stats-header').css( 'background-color', '#63AEE0');
  $( clickedClass ).find('.stats-header').css( 'color', '#ffffff');
}

/**
 *
 */
function others_statsClicked() {
  resetHeaders( '.other-form' );
  $('.victims-form').find(':input').attr("disabled", true).setValue(0);
  $('.political_affiliation-form').find(':input').attr("disabled", true).setValue(0);
  $('.other-form').find(':input').attr("disabled", false);
  
}

/**
 *
 */
function victimsClicked() {
  resetHeaders( '.victims-form' );
  $('.political_affiliation-form').find(':input').attr("disabled", true).setValue(0);
  $('.other-form').find(':input').attr("disabled", true).setValue(0);
  $('.victims-form').find(':input').attr("disabled", false);
}

/**
 *
 */
function political_affiliationClicked(){
  resetHeaders( '.political_affiliation-form' );
  $('.victims-form').find(':input').attr("disabled", true).setValue(0);
  $('.other-form').find(':input').attr("disabled", true).setValue(0);
  $('.political_affiliation-form').find(':input').attr("disabled", false);
}

/**
 *
 */
function updateFormVio(){
  var vioVal = $('#edit-violation-victim-options').val();
  //console.log( 'vioVal : ' + vioVal );
  switch( vioVal ){
    case 'total_violations':
      //console.log( 'called : ' + vioVal );
      $('#edit-int-standard-wrapper').hide();
      $('#edit-int-standard').val( 0 );
      break;
    case 'international_standards':
      //console.log( 'called : ' +vioVal );
      $('#edit-int-standard-wrapper').show();
      $('#edit-int-standard').val( 0 );
      break;
    default:
  }
}



