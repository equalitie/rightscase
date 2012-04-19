
Drupal.behaviors.correlative_form = function(context){
    
    
    updateFormVio();
    
    $('#edit-actor-options').change( function(){
      updateFormVio();
    });
    
    $('#edit-violation-options').change( function(){
      updateFormVio();
    });
    
};

function updateFormActor(  ){
  var actorVal = $('#edit-actor-options').val();
  console.log( 'called' );
  console.log( 'actorVal : ' + actorVal );
    switch(actorVal){
      case '1': //Age
        $('#edit-int-standard-wrapper').hide();
        $('#edit-violation-options').val( 0 );
        break;
      case '2': //Ethnicity
        $('#edit-int-standard-wrapper').show();
      break;
      case '3': //Gender
        $('#edit-int-standard-wrapper').show();
        break;
      case '4': //Political Affiliation
        $('#edit-int-standard-wrapper').hide();
        $('#edit-violation-options').val( 0 );
        //Drupal.messages.set('International Standard vs Political Affiliation is not available', 'notice');
        break;
      
    default:
    }
  
}

/*


*/
function updateFormVio(){
  var vioVal = $('#edit-violation-options').val();
  console.log( 'vioVal : ' + vioVal );
  switch( vioVal ){
    case '0':
      console.log( 'called : ' + vioVal );
      $('#edit-int-standard-wrapper').hide();
      $('#edit-int-standard').val( 0 );
      break;
    case '1':
          console.log( 'called : ' +vioVal );
      $('#edit-int-standard-wrapper').hide();
      $('#edit-int-standard').val( 0 );
      break;
    case '2':
        updateFormActor( );
      break;
    default:
  }
}



