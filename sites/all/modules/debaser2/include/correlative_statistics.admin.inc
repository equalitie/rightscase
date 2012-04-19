<?php
   
 function get_statistics_display(){
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
	$form['primary_field_type'] = array(
		'#title'=>t('Field'),
		'#type'=>'select',
		'#description'=>t('Select field for graph'),
		'#options'=>$form['field_options']['#value'],
	);
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
		'#value'=>$form_values['post']['previous'],
	);
	
	$form['submit'] = array(
		'#type'=>'submit',
		'#value'=>'Display Chart');
	
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
			if($sec_field==4){
				$max = get_victims_by_age_ethnicity($chart_data, $chart_labels);
				$title = t("Victims by Age Vs Ethnicity");
				$key = t('Ethnicity');
			}
			else{
				$title = get_victims_by_age_gender($chart_data, $chart_labels);
				
			} 
			$x_label = t('Age');
			$y_label = t('Victim');
		break;
		case 1:
			$location = $form_state['post']['location'];
			if($sec_field==2){
				$max = get_victims_by_location_gender($location, $chart_data, $chart_labels);
				$key = t('Gender');
				$title = t('Victims by Location Vs Gender');
			} else {
				$max = get_victims_by_location_ethnicity($location, $chart_data, $chart_labels);
				$title = t('Victims by Location Vs Ethnicity');
				$key = t('Ethnicity');
			}
			$x_label = t('Location');
			$y_label = t('Victim');
			
		break;
		case 2:
			$max = get_victims_by_gender_ethnicity($chart_data, $chart_labels);
			$title = t('Victims by Gender Vs Ethnicity');
			$key = t('Ethnicity');
			$x_label = t('Gender');
			$y_label = t('Victim');
		break;
		
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
	
	
	//include the graph functions
	$path = drupal_get_path('module', 'debaser2');
	require_once($path."/include/graph_generators.php");
  
	return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label, $y_label, $key, $max, $width, $height);
	
}


/***************************************** AGE GRAPH FUNCTIONS *****************************************/
/**
 * 
 * @param object $chart_data
 * @param object $title
 * @return 
 */
function get_victims_by_age_gender(&$chart_data, &$chart_labels) {
	$cases = array();
	$result = get_views_result('age_stats', "$location");
	if (count($result)) {
  		foreach ($result as $actor) {
  			$age = $actor->node_data_field_age_field_age_value;
			switch($age){
				case 0:
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
	return $title;
}

function get_victims_by_age_ethnicity(&$chart_data, &$chart_labels){
	$victims = array();
	$result = get_views_result('age_stats', "$location");
	if (count($result)) {
  		foreach ($result as $actor) {
  			$age = $actor->node_data_field_age_field_age_value;
			$node = node_load($actor->nid);
			$term_id = load_taxonomy_term($node->taxonomy, 4);
			switch($age){
				case 0:
				case $age<= 18:
					$victims['data'][$term_id->tid][0]++;
					$victims['labels'][0]=t('<18');
					break;
				case $age<= 35:
					$victims['data'][$term_id->tid][1]++;
					$victims['labels'][1]=t('19 - 35');
					break;
				case $age<= 50:
					$victims['data'][$term_id->tid][2]++;
					$victims['labels'][2]=t('35 - 50');
					break;
				case $age> 50:
					$victims['data'][$term_id->tid][3]++;
					$victims['labels'][3]=t('50 plus');
					break;		
			}
  		}
	}
	$i=0;
	foreach ($victims['data'] as $term_id => $ethnic_group) {
		$chart_data[$i]=array(
		'data' => $ethnic_group,
		'legend'=>get_term_name($term_id));
		$i++;
	}
	$chart_labels = $victims['labels'];	
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
function get_victims_by_location_gender($location, &$chart_data, &$chart_labels) {
	
	$victims = array();
	$name = '';
	$mca = array();//male case array
	$fca = array();//female case array
	$i=0;
	$j=0;
	$result = get_views_result('age_stats', "$location");
	
	if (count($result)) {
  		foreach ($result as $actor) {
  			// get the actor node
  			$node_actor = node_load($actor->nid);
			
			// get the case node associated with the actor
  			$nid = $node_actor->field_case[0]['nid'];
			$node_case = node_load($nid);
			
			//get the upper level region of the term associated with this node
			$term = load_taxonomy_term($node->taxonomy, REGION);
			$parent = taxonomy_get_parents($term->tid);
			$pid = get_parent_id($parent);
				if($location){
					if($pid==$location){
						if ($actor->node_data_field_age_field_gender_value=='female') {
		  				$victims['data']['female'][$pid]['total']++;
						$victims['data']['female'][$pid]['labels']=$parent[$pid]->name;
						
					}else{
						$victims['data']['male'][$pid]['total']++;
						$victims['data']['male'][$pid]['labels']=$parent[$pid]->name;
						
					}
					}
				}else{
		  			if ($actor->node_data_field_age_field_gender_value=='female') {
		  				$victims['data']['female'][$term->tid]['total']++;
						$victims['data']['female'][$term->tid]['labels']=$term->name;
						
					}else{
						$victims['data']['male'][$term->tid]['total']++;
						$victims['data']['male'][$term->tid]['labels']=$term->name;
						
					}
				}
		}
	}
	$location_labels = array();
	/*
	 * get the array with the most different regions in it
	 */
	$our_array = array();
	if (count($victims['data']['male'])>count($victims['data']['female'])) {
		$our_array = $victims['data']['male'];
	}else $our_array = $victims['data']['female'];
	
	$location_totals = array();
	
	$max = 0;
	foreach ($our_array as $location_id => $value) {
		/*
		 * get the total for each region or a zero if there is no victim associated with this region
		 */
		if($victims['data']['male'][$location_id]['total'])$m_total = $victims['data']['male'][$location_id]['total'];
		else $m_total = 0;
		if($victims['data']['female'][$location_id]['total'])$f_total = $victims['data']['female'][$location_id]['total'];
		else $f_total = 0;
		
		$location_totals[0][$i] = $m_total;
		$location_totals[1][$i] = $f_total;
		$chart_labels[$i] = get_term_name($location_id);
		$i++;
		
		if ($m_total>$max)$max=$m_total;
		if ($f_total>$max)$max=$f_total;
		
		
	}
	$chart_data[0]=array(
		'data' => $location_totals[0],
		'legend'=>t('Male'),);
	$chart_data[1]=array(
		'data' => $location_totals[1],
		'legend'=>t('Female'),);
		
	
	return $max;
}
/**
 * get numbers of victims by location correlated against their ethnicity 
 * @param object $location
 * @param object $chart_data
 * @param object $chart_labels
 * @return 
 */

function get_victims_by_location_ethnicity($location, &$chart_data, &$chart_labels) {
	$cases_age = array();
	$max = 0;
	$terms = taxonomy_get_tree(ETHNICITY);
	
	if(!$location){//top level region statistics
		$terms_location = taxonomy_get_tree(REGION);
		$j = 0;
		foreach ($terms as $ethnic_group) {
			$i=0;
			foreach ($terms_location as $location_term) {
				if ($location_term->depth==0) {
						$num_victims = count(get_views_result('location_ethnicity_stats', array($location_term->tid,$ethnic_group->tid)));
						$cases_age[$j][$i] = $num_victims;
						if($max<$num_victims)$max=$num_victims;
						$i++;
						$chart_labels[$i] = $location_term->name;
				}		
			}
			$j++;
		}
	}else{//sub region statistics
		$j = 0;
		$terms_location = taxonomy_get_tree(REGION, $location);
		//dprint_r($terms_location);
		foreach ($terms as $ethnic_group) {
			$i=0;
			foreach ($terms_location as $location_term) {
				$num_victims = count(get_display_result('location_ethnicity_stats', array($ethnic_group->tid, $location_term->tid)));
				$cases_age[$j][$i] = $num_victims;
				if($max<$num_victims)$max=$num_victims;
				$chart_labels[$i] = $location_term->name;
				$i++;
			}
			$j++;
			
		}
	}
	$i=0;
	foreach($cases_age as $case){
		$chart_data[$i]=array(
		'data' => $cases_age[$i],
		'legend'=>get_term_name($terms[$i]->tid));
		$i++;
	}
	
	return $max;
}


/********************************************************************************************************/


function get_victims_by_gender_ethnicity(&$chart_data, &$chart_labels){
	$victims = array();
	$result = get_views_result('gender_stats');
	
	$terms = taxonomy_get_tree(ETHNICITY);
	
	
	$i=0;
		foreach($terms as $ethnic_group){
			//get the number of men per ethnic group
			$arguments = array($ethnic_group->tid, "male");
			$num_victims = count(get_views_result('gender_stats', $arguments));
			$victims[$i][0]  = $num_victims;
			if($max<$num_victims)$max=$num_victims;
			//get the number of women per ethnic group
			$num_victims = count(get_views_result('gender_stats', array($ethnic_group->tid, "female")));
			$victims[$i][1] = $num_victims;
			$i++;
			
		}
	$i=0;
	$chart_labels = array('Male', 'Female');
	foreach($victims as $victim){
		$chart_data[$i]=array(
		'data' => $victim,
		'legend'=>get_term_name($terms[$i]->tid));
		$i++;
	}
	
	return $max;
	
}
