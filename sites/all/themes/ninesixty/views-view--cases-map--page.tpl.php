<div class="<?php print $classes; ?>">
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <script type="text/javascript">
        var statMarker = [];
      </script>
      <?php print $rows; ?>
      <div id="stat_map" style="width: 100%; height: 650px;"></div>
      <script type="text/javascript">
        (function($){
          var map, infowindow;
          $(function() {
            var infowindow = new google.maps.InfoWindow({});
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
            map = new google.maps.Map($('#stat_map').get(0), mapOptions);
            for (var i = 0; i < statMarker.length; i++) {
              var coords = statMarker[i].coords.split(","),
                  position = new google.maps.LatLng(Number(coords[0]), Number(coords[1]));

              var marker = new google.maps.Marker({
                position: position,
                map: map,
                title: statMarker[i].title
              });

              (function(marker, data) {
                google.maps.event.addListener(marker, 'click', function() {
                  infowindow.open(map, marker);
                  infowindow.setContent(data.content);
                });
              })(marker, statMarker[i]);
            }
          });
        })(jQuery);
      </script>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div> <?php /* class view */ ?>