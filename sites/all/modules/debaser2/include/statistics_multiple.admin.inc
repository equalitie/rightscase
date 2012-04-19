<?php
   
 function debaser2_correlative_page_old(){
	drupal_add_js('sites/all/modules/debaser2_custom/js/jquery.selectboxes.js');
	drupal_add_js('sites/all/modules/debaser2_custom/js/jquery.field.js');
	drupal_add_js('sites/all/modules/debaser2_custom/js/form_manipulation.js');
	return drupal_get_form('correlative_statistics_form');
	
	
}

/**
 * build a multistep form to allow post results to be sent back to the same page
 * @param object $form_values [optional]
 * @return 
 */

function correlative_statistics_form($form_values = NULL){
	$form['#multistep'] = TRUE;
  	$form['#redirect'] = FALSE;

	$form['field_options'] = array(
		'#type'=>'value',
		'#value'=>array(t('Age of Victim'), t('Location of Violation'), t('Gender of Victim '), t('Violation Type'), t('Date of Violation'), t('Case Status'), ),	  
	);
	$form['field_options_2'] = array(
		'#type'=>'value',
		'#value'=>array()
	);
	$form['chart_type'] = array(
		'#title'=>t('Chart type'),
		'#type'=>'select',
		'#description'=>t('Select field for graph'),
		'#options'=>array(0=>t('Bar Chart'), 1=>t('Pie Chart')),
	);
	/*$form['primary_field_type'] = array(
		'#title'=>t('Field'),
		'#type'=>'select',
		'#description'=>t('Select field for graph'),
		'#options'=>$form['field_options']['#value'],
	);*/
	$form['location'] = select_region_widget();
	$form['secondary_field_type'] = array(
		'#title'=>t('Field'),
		'#type'=>'select',
		'#description'=>t('Select field for graph'),
		'#options'=>$form['field_options']['#value'],
	);
	
	
	
	$form['previous'] = array(
		'#title'=> 'previous',
		'#type'=>'hidden',
		'#id'=>'previous',
		
	);
	
	$form['submit'] = array(
		'#type'=>'submit',
		'#value'=>t('Display Chart')
	);
	
	if ($form_values!=NULL) {
		$form['results'] = array(
	      '#type' => 'item',
	      '#value' => correlative_statistics_form_handling($form_values),
	    );
	}
	
		return $form;
	
}

function correlative_statistics_form_handling(&$form_state){
	$field = $form_state['post']['primary_field_type'];
	$sec_field = $form_state['post']['secondary_field_type'];
	
	$chart_data = array();
	$chart_labels = array();
	$title = '';
	switch($field){
		case 0:
			if($sec_field==4)$title = get_cases_by_age_ethnicity($chart_data, $chart_labels);
			else $title = get_cases_by_age_gender($chart_data, $chart_labels);
		break;
		case 1:
			$location = $form_state['post']['location'];
			if($sec_field==2){
				$title = get_cases_by_location_gender($location, $chart_data, $chart_labels);
			} else {
				$title = get_cases_by_location_ethnicity($location, $chart_data, $chart_labels);
			}
	}
	/*$chart_data[0] = array(
	'data'=>array(10, 20, 15, 30),
	'legend'=>'legend1',
	);
	$chart_data[1] = array(
	'data'=>array(20, 15, 30, 10),
	'legend'=>'legend2',
	);
	$chart_labels = array('label 1', 'label 2', 'label 3', 'label 4');
	$title = "My title";
	$width = 800;
	$height = 800;*/
	
	
	
	
	return multi_bar_chart($chart_data, $chart_labels, $title, $width, $height);
	
}

/********************************************************************************************************/

/***************************************** AGE GRAPH FUNCTIONS *****************************************/
/**
 * 
 * @param object $chart_data
 * @param object $title
 * @return 
 */
function get_cases_by_age_gender(&$chart_data, &$chart_labels) {
	$cases = array();
	$title = "Cases by Age Vs Gender";
	$view = views_get_view('age_stats');
	$view->execute();
	$i=0;
	if (count($view->result)) {
  		foreach ($view->result as $actor) {
  			$age = $actor->node_data_field_age_field_age_value;
			switch($age){
				case $age<= 18:
					if ($actor->node_data_field_age_field_gender_value=='female') {
						$cases['data']['female'][0]++;
					}else $cases['data']['male'][0]++;
					$cases['labels'][0]=t('<18');
					break;
				case $age<= 35:
					if ($actor->node_data_field_age_field_gender_value=='female') {
						$cases['data']['female'][1]++;
					}else $cases['data']['male'][1]++;
					$cases['labels'][1]=t('19 - 35');
					break;
				case $age<= 50:
					if ($actor->node_data_field_age_field_gender_value=='female') {
						$cases['data']['female'][2]++;
					}else $cases['data']['male'][2]++;
					$cases['labels'][2]=t('35 - 50');
					break;
				case $age> 50:
					if ($actor->node_data_field_age_field_gender_value=='female') {
						$cases['data']['female'][3]++;
					}else $cases['data']['male'][3]++;
					$cases['labels'][3]=t('50 plus');
					break;		
			}
  		}
	}
	$chart_data[0]=array(
		'data' => $cases['data']['male'],
		'legend'=>'Male');
	
	$chart_data[1]=array(
	'data' => $cases['data']['female'],
	'legend'=>'Female');
	
	$chart_labels = $cases['labels'];
	
}

function get_cases_by_age_ethnicity(&$chart_data, &$chart_labels){
	$cases = array();
	$title = t("Cases by Age Vs Ethnicity");
	$view = views_get_view('age_stats');
	$view->execute();
	$i=0;
	if (count($view->result)) {
  		foreach ($view->result as $actor) {
  			$age = $actor->node_data_field_age_field_age_value;
			$node = node_load($actor->nid);
			$term_id = load_taxonomy_term($node->taxonomy, 4);
			switch($age){
				case $age<= 18:
					$cases['data'][$term_id->tid][0]++;
					$cases['labels'][0]=t('<18');
					break;
				case $age<= 35:
					$cases['data'][$term_id->tid][1]++;
					$cases['labels'][1]=t('19 - 35');
					break;
				case $age<= 50:
					$cases['data'][$term_id->tid][2]++;
					$cases['labels'][2]=t('35 - 50');
					break;
				case $age> 50:
					$cases['data'][$term_id->tid][3]++;
					$cases['labels'][3]=t('50 plus');
					break;		
			}
  		}
	}
	$i=0;
	
	foreach ($cases['data'] as $term_id => $ethnic_group) {
		$chart_data[$i]=array(
		'data' => $ethnic_group,
		'legend'=>get_term_name($term_id));
		$i++;
	}
	$chart_labels = $cases['labels'];	
	return $title;
	
}

/********************************************************************************************************/

/************************************* LOCATION GRAPH FUNCTIONS *****************************************/

/**
 * first we need to get a list of the victims and get the case links
 * then we sort the cases by location
 * @param object $location
 * @param object $chart_data
 * @param object $chart_labels
 * @return 
 */
function get_cases_by_location_gender($location, &$chart_data, &$chart_labels) {
	$title = t('Cases by Location Vs Gender');
	$cases_age = array();
	$mca = array();//male case array
	$fca = array();//female case array
	$i=0;
	$j=0;
	$result = get_views_result('age_stats', "$location");
	
	if (count($result)) {
  		foreach ($result as $actor) {
  			if ($actor->node_data_field_age_field_gender_value=='female') {
  				$fca[$i] = $actor->node_data_field_case_field_case_nid;
				$i++;
			}else{
				$mca[$j] = $actor->node_data_field_case_field_case_nid;
				$j++;
			}
		}
	}
	return $title;
}

function get_cases_by_location_ethnicity($location, &$chart_data, &$chart_labels) {
	$cases_age = array();
	$view = views_get_view('age_stats');
	$view->set_items_per_page(0);
	if($location)$view->set_arguments(array("$location"));
	
	$view->execute();
	if (count($view->result)) {
  		foreach ($view->result as $actor) {
		}
	}
}


/********************************************************************************************************/



/***************************************** AGE GRAPH FUNCTIONS *****************************************/



/********************************************************************************************************/


