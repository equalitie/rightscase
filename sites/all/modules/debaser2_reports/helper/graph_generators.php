<?php

/** 
 *
 *This class is used to display a simple Bar Graph
 *
 */
class ChartData{
  public $data             = null;
  
  private $barGraph           = null;
  private $pieGraph           = null;
  private $max             = 0;
  private $internal_labels = array();
  private $chart_labels    = array();
  
  private $prepared_data   = array();



  function __construct( $data ){
    $this->data = $data;
    $this->initGraph();
  }
  
  public function drawGraph(){
    return $this->renderGraph();
  }

  public function outputPieGraph(){
    return $this->pieOutput;
  }

  private function initGraph(){
    $this->barGraph = new open_flash_chart_api();
    $this->barGraph->title( $this->data['title'],
      '{font-size:10px;'. 
        'color: #FFFFFF;'. 
        'margin: 5px;'. 
        'background-color: #505050;'. 
        'padding:5px;'. 
        'padding-left: 20px;'. 
        'padding-right: 20px;'.
        '}'
     );
    $this->setDimensions();
    $this->prepareData();
    if( count( $this->data['chart_data'] ) === 1){
      $this->createPieSlices();
    }
    $this->createBars();
  }
  
  private function setDimensions(){
    $this->barGraph->set_width( 890 );
    $this->barGraph->set_height( 300 );
  }

  private function prepareData(){
    $i=0;
	  foreach ($this->data['chart_data'] as $row ) {
       foreach( $row['data'] as $value ){
         $this->checkMax( $value );
       }
  	}
  }
  
  private function createBars(){
	  $i=0;
	  foreach ($this->data['chart_data'] as $data) {
		  $vals = $data['data'];
		  $bar = new bar( 80, $this->presetColours( $i ) );
      if( $data['legend'] ){
		    $bar->key($data['legend'], 10);
        $this->barKey = '<br>#key#';
      }else{
        $this->barKey = '';
      }
		  $bar->data = $vals;
		  $this->barGraph->data_sets[] = $bar;
		  $i++;
	  }
  }
  
  private function createPieSlices(){
    $colors = array();
    for ($i = 0; $i < count( $this->data['chart_data'][0]['data'] ); $i++) {
        $colors[$i] = $this->presetColours($i);
    }
    $this->pieGraph = new open_flash_chart_api();
    $this->pieGraph->pie(60, '#505050', 
      '{font-size:10px;'. 
        'color: #505050;'. 
        'margin: 5px;'. 
        'background-color: #ffffff;'. 
        'padding:5px;'. 
        'padding-left: 90px;'. 
        'padding-right: 90px;'.
        '}'
      );
    $this->pieGraph->pie_values( $this->data['chart_data'][0]['data'], $this->data['chart_labels'] );
    $this->pieGraph->pie_slice_colours($colors);
    $this->pieGraph->set_tool_tip( $this->data['title'].
        '<br>'.$this->data['key'].': #x_label#'.
        '<br>'.  $this->data['y_label'] . ': #val# '
        );
    $this->pieGraph->set_width( 890 );
    $this->pieGraph->set_height(350);
    $this->pieOutput = $this->pieGraph->render();
  }

  /*
  check if the label already exists for this bar
  */
  private function check_label_exists( &$array, $label ){

    $pos = array_search( $label, $array );
    if( $pos === false ) {
      $array[] = $label;
      return ( count( $array ) - 1 ); 
    } else {
      return $pos;
    }

  }
  

  /*
  find the maximum value for the graph this ensures that all data is within the axis ranges
  */
  private function checkMax( $value ){
    if ( $value > $this->max ) $this->max = $value;
  }

  private function renderGraph(){

    $this->barGraph->x_axis_colour('#909090', '#ADB5C7');
    $this->barGraph->y_axis_colour('#909090', '#ADB5C7');
    $this->barGraph->set_tool_tip( $this->data['title'].
        $this->barKey .
        '<br>'.$this->data['key'].': #x_label#'.
        //'<br>'.$key.': #x_label#'.
        //'<br>'.$x_label.': #x_label#'.
        '<br>'.$this->data['y_label'].': #val#' );
    $this->barGraph->set_x_labels($this->data['chart_labels']);
    $this->barGraph->set_y_max( $this->max + 1  );
    $this->barGraph->y_label_steps(5);
    $this->barGraph->set_y_legend($this->data['y_label'], 12, '#736AFF');
    $this->barGraph->set_x_legend($this->data['x_label'], 12, '#736AFF');
    $this->barGraph->set_bg_colour('0xFFFFFF');
    return $this->barGraph->render();
  }

  /*
  a list of usable colours for the bar charts
  */
  private function presetColours( $i ){
	$colours = array(
	'#49aab7', '#e38e8e', '#449194', '#8ee38e', '#49b74d',
	'#b749b3', '#b78749', '#4975b7', '#49b79f', '#7cb749',
	'#239999', '#992399', '#999923', '#aa49b7',
	);
	return $colours[$i];
  }

}
