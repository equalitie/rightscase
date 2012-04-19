<?php

function multi_bar_chart($chart_data, $chart_labels, $title, $width, $height) {

    $g = new open_flash_chart_api();
    
    $i=0;
    foreach ($chart_data as $data) {
      $vals = $data['data'];
      $bar = new bar(12, presetColours($i));
      $bar->key($data['legend'], 10);
      $bar->data = $vals;
      
      $g->data_sets[] = $bar;
      $i++;
    }
 
    
    // create the graph object:
    
    $g->title($title . 'hello', '{font-size:10px; color: #FFFFFF; margin: 5px; background-color: #505050; padding:5px; padding-left: 20px; padding-right: 20px;}');
    $g->set_width(500);
	  $g->set_height(500);
   
    
    //$g->set_x_axis( 12 );
    $g->x_axis_colour('#909090', '#ADB5C7');
    $g->y_axis_colour('#909090', '#ADB5C7');
    $g->set_tool_tip( '#key#: #val# cases (#x_label#)<br>Key: #key#<br>Age: #x_label#<br>Cases: #val#' );
    $g->set_x_labels($chart_labels);
    $g->set_y_max(10);
    $g->y_label_steps(5);
    $g->set_y_legend(t('Cases'), 12, '#736AFF');
    return $g->render();
}

/**
this creates pretty much all the charts

*/

function correlative_bar_chart($chart_data, $chart_labels, $title, $x_label, $y_label, $key, $max = 150, $width =500, $height = 500) {
  
  dpm( '$chart_data' );
  dpm( $chart_data );
  dpm( '$chart_labels' );
  dpm( $chart_labels );
  dpm( '$title' );
  dpm( $title );
  dpm( '$x_label' );
  dpm( $x_label );
  dpm( '$y_label' );
  dpm( $y_label );
  
  dpm( '$key' );
  dpm( $key );
  

  if( !debaser2_data_is_ok($chart_data) ) {
    return debaser2_without_data();
  } 

    $g = new open_flash_chart_api();
    $mod = $max%10;
    $max +=10-$max%10;
    $g->set_width(880);
    $g->set_height(300);
    $i=0;
    foreach ($chart_data as $data) {
      
      $vals = $data['data'];

      $bar = new bar(80, presetColours($i));
      $bar->key($data['legend'], 10);
      $bar->data = $vals;
      
      $g->data_sets[] = $bar;
      $i++;
    }
 
    
    // create the graph object:
    
    $g->title($title, '{font-size:10px; color: #FFFFFF; margin: 5px; background-color: #505050; padding:5px; padding-left: 20px; padding-right: 20px;}');
    
   
    
    //$g->set_x_axis( 12 );
    $g->x_axis_colour('#909090', '#ADB5C7');
    $g->y_axis_colour('#909090', '#ADB5C7');
    $g->set_tool_tip( $title.'<br>'.$key.': #x_label#'.
        //'<br>'.$key.': #x_label#'.
        //'<br>'.$x_label.': #x_label#'.
        '<br>'.$y_label.': #val#' );
    $g->set_x_labels($chart_labels);
    $g->set_y_max($max);
    $g->y_label_steps(5);
    $g->set_y_legend($y_label, 12, '#736AFF');
    $g->set_x_legend($x_label, 12, '#736AFF');
    $g->set_bg_colour('0xFFFFFF');
    return $g->render();

}

function debaser2_new_correlative_bar_chart($chart_data, $title, $x_label, $y_label, $key, $max = 150, $width =500, $height = 500) {
  
  dpm( '$chart_data' );
  dpm( $chart_data );
  dpm( '$chart_labels' );
  dpm( $chart_labels );
  dpm( '$title' );
  dpm( $title );
  dpm( '$x_label' );
  dpm( $x_label );
  dpm( '$y_label' );
  dpm( $y_label );
 
  dpm( '$key' );
  dpm( $key );
  

  if( !debaser2_data_is_ok($chart_data) ) {
    return debaser2_without_data();
  }

    $total = 0;
 
    $g = new open_flash_chart_api();
	  $g->set_width(880);
	  $g->set_height(300);
	  $chart_labels = array();
  	$internal_labels = array();
  
    foreach($chart_data as $values) {
      foreach($values as $k => $t) {
        if ($t > $total) {
          $total = $t;
        } 
      }
    }
  
    // dpm((int)($total*1.2));  
    $max = $total;
    $mod = $max%10;
	  $max += 10-$max%10;
	  $i=0;
    $j=0;
	
	  foreach ($chart_data as $year => $data) {
	    $chart_labels[] = $year;
	    foreach ($data as $label => $value){
	      $index = _debaser2_check_label_exists( $internal_labels, $label );
	      $my_data[$index]['data'][$i] = $value;
	      $my_data[$index]['legend'] = $label;
	    }
	    $i++;
  	}
	
	  $i=0;
	  foreach ($my_data as $data) {
		  $vals = $data['data'];
		  $bar = new bar(80, presetColours($i));
		  $bar->key($data['legend'], 10);
		  $bar->data = $vals;
		  $g->data_sets[] = $bar;
		  $i++;
	  }

    // create the graph object:
    
    $g->title($title, '{font-size:10px; color: #FFFFFF; margin: 5px; background-color: #505050; padding:5px; padding-left: 20px; padding-right: 20px;}');
    
   
    
    //$g->set_x_axis( 12 );
    $g->x_axis_colour('#909090', '#ADB5C7');
    $g->y_axis_colour('#909090', '#ADB5C7');
    $g->set_tool_tip( $title.
        '<br>#key#'.
        '<br>'.$key.': #x_label#'.
        //'<br>'.$key.': #x_label#'.
        //'<br>'.$x_label.': #x_label#'.
        '<br>'.$y_label.': #val#' );
    $g->set_x_labels($chart_labels);
    $g->set_y_max($max);
    $g->y_label_steps(5);
    $g->set_y_legend($y_label, 12, '#736AFF');
    $g->set_x_legend($x_label, 12, '#736AFF');
    $g->set_bg_colour('0xFFFFFF');
    return $g->render();
   
}


/**
 *
 */
function _debaser2_check_label_exists( &$array, $label ){

  $pos = array_search( $label, $array );
  if( $pos === false ) {
    $array[] = $label;
    return ( count( $array ) - 1 ); 
    
  } else {

    return $pos;
  }
  
}




function generate_bar_chart($chart_data, $chart_labels, $title, $width, $height, $y_legend='Cases') {
    $g = new open_flash_chart_api();
    $g->title($title, '{font-size:10px; color: #FFFFFF; margin: 5px; background-color: #505050; padding:5px; padding-left: 20px; padding-right: 20px;}');
    $g->set_width(680);
    $g->set_height(300);
    
    //
    // BAR CHART:
    //
    $g->set_data( $chart_data );
    $g->bar( 80, presetColours(0), t('Number of ') .$y_legend, 10 );
    //
    // ------------------------
    //
    
    //
    // X axis tweeks:
    //
    $g->set_x_labels( $chart_labels );
    //
    // set the X axis to show every 2nd label:
    //
    $g->set_x_label_style( 10, '#9933CC', 0, 1 );
    //
    // and tick every second value:
    //
    $g->set_x_axis_steps( 1 );
    //
    
    
    $g->y_label_steps( 4 );
    $g->set_y_legend( $y_legend, 12, '#736AFF' );
    $g->set_bg_colour('0xFFFFFF');
    return $g->render();

}


/**
 * generates a pie chart based on the data from the user
 * @param int array $chart_data
 * @param String $chart_labels
 * @param String $title title of the graph
 * @param int $width
 * @param int $height
 * @return The javascript needed to embed the graph
 */
function generate_pie_chart($chart_data, $chart_labels, $title, $width, $height, $y_legend) {
    drupal_add_js($base_path."/sites/all/modules/debaser2_custom/swfobject/swfobject.js");
    
    $colors = array();
    for ($i = 0; $i < count($chart_data); $i++) {
        $colors[$i] = presetColours($i);
    }
    $chart = new open_flash_chart_api();
    $chart->pie(60, '#505050', '{font-size: 12px; color: #404040;');
    $chart->pie_values($chart_data, $chart_labels);
    $chart->pie_slice_colours($colors);
    $chart->set_tool_tip('Value: #val# '.$y_legend.' ');
    $chart->title($title, '{font-size:18px; color: #d01f3c}');
    $chart->set_width($width);
    $chart->set_height($height);
    return $chart->render();

}

function debaser2_data_is_ok($data){
  // debug_print_backtrace();
  // drupal_set_message('<pre>'. print_r(debug_backtrace(), 1) .'</pre>', 'error');
  // dpm($data);
  $return = true;
  if ( empty($data)) {
    $return = false;
  } else {
    $first_row = array_shift($data);
    if ( empty($first_row)) {
      $return = false;
    } else {
      $second_level_first_row = array_shift($first_row);
      if ( empty($second_level_first_row)) {
        $return = false;
      } 
    }
  }

  return $return;

}

function debaser2_without_data(){
  return '<h4>No results found.</h4>';
}

function presetColours($i){
	$colours = array(
	'#49aab7',
	'#e38e8e',
	'#449194',
	'#8ee38e',
	'#49b74d',
	'#b749b3',
	'#b78749',
	'#4975b7',
	'#49b79f',
	'#7cb749',
	'#239999',
	'#992399',
	'#999923',
	'#aa49b7',
	
	);
	return $colours[$i];
}

function randomColour(){
	srand((double) microtime() * 1004000);
	$colors = sprintf("#%u%u%u%u%u%u", dechex(mt_rand(0, 15)), dechex(mt_rand(0, 15)), dechex(mt_rand(0, 15)), dechex(mt_rand(0, 15)), dechex(mt_rand(0, 15)), dechex(mt_rand(0, 15)));
	return $colors;
}
