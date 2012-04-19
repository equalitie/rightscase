  (function($) {
    var map, geocoder,
        currentMarker,
        markers = '';/*<?php echo json_encode($markers); ?>;*/

    function SearchBox() {
      var searchTextBox = $('<input type="text" id="txtGeoSearch" name="geo_search" />').css({
          border: '1px solid #ccc'
        });
      searchTextBox.autocomplete({
          source: function(request, response) {
            geocoder.geocode({
                'address': request.term
              }, function(results, status) {
              response($.map(results, function(item) {
                return {
                  label: item.formatted_address,
                  value: item.formatted_address,
                  latitude: item.geometry.location.lat(),
                  longitude: item.geometry.location.lng()
                };
              }));
            });
          },
          select: function(event, ui) {
            var location = new google.maps.LatLng(ui.item.latitude, ui.item.longitude);
            map.setCenter(location);
          }
        });

      var div = $('<div class="geoSearchBox"></div>').append($('<span>Search:</span>').css({
          marginRight: '5px'
        })).append(searchTextBox).css({
          backgroundColor: '#fff',
          padding: '10px',
          marginBottom: '20px',
          font: 'bold 11px Tahoma',
          opacity: 0.95
        });
      return div.get(0);
    }

    function placeMarker(map, location) {
      var marker = new google.maps.Marker({
        position: location,
        map: map,
        draggable: true
      });

      currentMarker = marker;
      marker.input = $('<input name="location_markers[]" type="hidden" value="" />').val(location.toUrlValue()).prependTo('#node-form');

      google.maps.event.addListener(marker, 'click', function() {
        if (currentMarker) {
          currentMarker.setAnimation(null);
        }
        currentMarker = marker;
        if (marker.getAnimation() != null) {
           marker.setAnimation(null);
        } else {
          marker.setAnimation(google.maps.Animation.BOUNCE);
        }
      });

      google.maps.event.addListener(marker, 'dragend', function(event) {
        marker.input.val(event.latLng.toUrlValue());
      });
    }

    function removeMarker() {
      if (currentMarker) {
        currentMarker.input.remove();
        currentMarker.setMap(null);
        currentMarker = null;
      }
    }

    $(function() {
      console.log('running the function');
      var latLng = new google.maps.LatLng(-19.13913474945349, 29.912109375);
      var mapOptions = {
        zoom: 5,
        center: latLng,
        panControl: true,
        zoomControl: true,
        zoomControlOptions: {
          style: google.maps.ZoomControlStyle.SMALL
        },
        scaleControl: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      map = new google.maps.Map($('.map_field').get(0), mapOptions);
      geocoder = new google.maps.Geocoder();
      map.controls[google.maps.ControlPosition.BOTTOM_CENTER].push(new SearchBox());

      google.maps.event.addListener(map, 'click', function(event) {
        placeMarker(map, event.latLng);
      });

      $('input.delete-marker').click(removeMarker);
      if (markers.length) {
        for (var i = 0; i < markers.length; i++) {
          var pos = markers[i].split(',');
          try {
            placeMarker(map, new google.maps.LatLng(Number(pos[0]), Number(pos[1])));
          } catch(e) {
          }
        }
      }

      console.log(latLng);
      console.log(location);
      console.log(mapOptions);
      console.log(map);
      console.log(geocoder);
    });

  })(jQuery);

