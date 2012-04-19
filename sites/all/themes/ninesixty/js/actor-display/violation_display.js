/**
 * @author cormac1
 * views-cycle-case_actors-page_2
 */
$(document).ready(function(){

    $('.violation-pager a').click(function(event){
        event.preventDefault();
    });

    $('.violation-pager').click(function(){
        HtmlLoader.url = $(this).children().attr('href');
        HtmlLoader.loadHtmlContent();
        $(this).addClass('activeSlide');
	$(this).siblings().removeClass('activeSlide');
    });

    $( '.violation-pager:first' ).trigger( 'click' );
});


var HtmlLoader = {
    url:null,
    jsonArray:null,
    
    
    loadHtmlContent:function(){
        $.getJSON(this.url, this.parseJSON)
    },
    
    applyHtml: function(html){
        $('#violation-container').empty();
        $('#violation-container').append(html);
    }, 

    parseJSON:function(json){
       this.jsonArray = json;
       HtmlLoader.applyHtml(json['html_content']);
       MYMAP.run(json['latlng']);
        
    }

}

//this handles the updating of the maps


var MYMAP = {
  bounds: null,
  map: null
}

MYMAP.run = function(points){
  var myLatLng = new google.maps.LatLng( points[0].lat, points[0].lng );
  MYMAP.init(myLatLng, '#mapholder' , 11);
  MYMAP.placeMarkers( points );
}


MYMAP.init = function(latLng, selector, zoom) {
  var myOptions = {
    zoom:zoom,
    center: latLng,
    mapTypeId: google.maps.MapTypeId.ROADMAP
  }
  this.map = new google.maps.Map($(selector)[0], myOptions);
  this.bounds = new google.maps.LatLngBounds();
}


MYMAP.placeMarkers = function(myPoints) {

   for( key in myPoints ){
      var name = $(this).find('name').text();
      var address = $(this).find('address').text();
      var lat = myPoints[key].lat;
      var lng = myPoints[key].lng;
      
      
      
      var point = new google.maps.LatLng(parseFloat(lat),parseFloat(lng));
      // extend the bounds to include the new point
      MYMAP.bounds.extend(point);
      // add the marker itself
      var marker = new google.maps.Marker({
        position: point,
        map: MYMAP.map
      });
      // create the tooltip and its text
      var infoWindow = new google.maps.InfoWindow();
      var html='<b>'+name+'</b><br />'+address;
      // add a listener to open the tooltip when a user clicks on one of the markers
      google.maps.event.addListener(marker, 'click', function() {
        
      });
    }
    
    
    
    // Fit the map around the markers we added:
    if(myPoints.length>1)MYMAP.map.fitBounds(MYMAP.bounds);

}
