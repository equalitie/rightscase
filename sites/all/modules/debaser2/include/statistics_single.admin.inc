<?php
/*
 * This file will handle the generation of charts based on a single field from the database
 *
 */



function get_statistics_display(){
	
	return drupal_get_form('statistics_form');
}

/**
 * build a multistep form to allow post results to be sent back to the same page
 * @param object $form_values [optional]
 * @return 
 */
function statistics_form( $form_values = NULL ){
	$location = get_taxonomy(REGION);
	$status = get_taxonomy(CASESTATUS);
	$form['#multistep'] = TRUE;
 
  	$form['#redirect'] = FALSE;
	$form['field_options'] = array(
		'#type'=>'value',
		'#value'=>array(
			0=>t('<select>'), 1=>t('Actor Type'), 2=>t('Gender'), 3=>t('Ethnicity'), 4=>t('Political affiliation'), 5=>t('Age'), 
		),
	);
	$form['actor_type'] = array(
		'#title'=>t('Actor type'),
		'#type'=>'select',
		'#description'=>t('Select actor type'),
		'#options'=>array(0=>t('<all actors>'), 2=>t('Perpetrator'), 1=>t('Victim'), 3=>t('Witness')),
	);
	$form['case_options'] = array(
		'#title'=>t('Case Filters'),
		'#type'=>'select',
		'#description'=>t('Select case filter'),
		'#options'=>array(0=>t('<select>'), 1=>t('Status'), 2=>t('Reason for Intervention'), 3=>t('Date of Intervention'), ),
	);
	
	$form['case_location_options'] = array(
		'#title' => t('Case Location'),
		'#type' => 'select',
		'#description'=>t('Select case location'),
		'#options' =>$location,
	);
	$form['case_status_options'] = array(
		'#title' => t('Case Status'),
		'#type' => 'select',
		'#description'=>t('Select case status'),
		'#options' =>$status,
	);
	
	$form['violation_options'] = array(
		'#title'=>t('Violation Filters'),
		'#type'=>'select',
		'#description'=>t('Select violation filter'),
		'#options'=>array(0=>t('<select>'), 1=>t('Case Status'), 2=>t('Date(months)'), 3=>t('Date(years)'), /*4=>t('International Standard'),*/ ),
	);
	
	$form['violation_location_options'] = array(
	'#title' => t('Violation Location'),
	'#type' => 'select',
	'#description'=>t('Select violation location'),
	'#options' =>$location,
	);
	
	$form['chart_type'] = array(
		'#title'=>t('Chart type'),
		'#type'=>'select',
		'#description'=>t('Select field for graph'),
		'#options'=>array(0=>t('Bar Chart'), 1=>t('Pie Chart')),
	);
	$form['field_type'] = array(
		'#title'=>t('Actor Filters'),
		'#type'=>'select',
		'#description'=>t('Select actor filter'),
		'#options'=>$form['field_options']['#value'],
	);
	
	if($form_values['post']['location'])$collapsed = FALSE;
	else $collapsed = TRUE;
	$form['region'] = array(
		'#title'=> t('Select Region'),
		'#type'=>'fieldset',
		'#collapsible'=>TRUE,
		'#collapsed'=>$collapsed,
		
	);
	$form['region']['location'] = select_region_widget();
	
	$form['submit'] = array(
		'#type'=>'submit',
		'#value'=>t('Display Chart'),
	);
	
	if ($form_values!=NULL) {
		$form['results'] = array(
	      '#type' => 'item',
	      '#value' => statistics_form_handling($form_values),
	    );
	}
	return $form;
	
		
}

/*********************************************************************************************************/
/**
 * handle the results of the criteria selection
 * @param object $form
 * @param object $form_state
 * @return 
 */

function statistics_form_handling(&$form_state){
  /*
  new method of calculating stats see /include/single_stats_new.admin.inc
  */
  $path = drupal_get_path('module', 'debaser2');
  include($path . '/include/single_stats_new.admin.inc');
  $new_chart = debaser2_new_stats_handling($form_state['post']);
  if($new_chart)return $new_chart;
  dpm ( '************************* old ****************************************** ' ); 
  //dpm( $form_state );
  /*
  old method using views
  */
	$field = $form_state['post']['field_type'];
	$case_stats_flag = $form_state['post']['case_options'];
	$case_loc_flag = $form_state['post']['case_location_options'];
	$case_status_flag = $form_state['post']['case_status_options'];
	$vio_stats_flag = $form_state['post']['violation_options'];
	$vio_loc_flag = $form_state['post']['violation_location_options'];
	
	$actor_type = $form_state['post']['actor_type'];
	$location = $form_state['post']['location'];
	//array containing all actor types
	$term_ids = array( 2=>'Perpetrators', 1=>'Victims', 3=>'Witnesses');
	
	//drupal_set_message($form['field_options']['#value'][$field].t(' selected'));
	//include the graph functions
	$path = drupal_get_path('module', 'debaser2');

	require_once($path."/include/graph_generators.php");
	drupal_add_js($path."/swfobject/swfobject.js");
  $width = 500;
  $height = 500;
	$y_legend = "Cases";
	if($field){
		switch($field){//HANDLE ACTOR SELECTIONS
			case 1://Actors by Type
				if($actor_type){
					$term_ids = truncate_array($term_ids, $actor_type);
					$y_legend = $term_ids[$actor_type];
					$x_label = t('Actor Type');
				}else{
					$y_legend = t("Actors");
					$x_label = t('Type');
				}
				$title = get_actors_by_type($chart_data, $chart_labels, $term_ids);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Type');
				break;
				
			case 2://Gender
				if($actor_type){
					$term_ids = truncate_array($term_ids, $actor_type);
					$y_legend = $term_ids[$actor_type];
					$x_label = t('Actor Type');
				}else{
					$y_legend = t("Actors");
					$x_label = t('Type');
					
				}
				$title = get_actors_by_gender($chart_data, $chart_labels, $term_ids);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Gender');
				break;
				
			case 3://Ethnicity
				if($actor_type){
					$term_ids = truncate_array($term_ids, $actor_type);
					$y_legend = $term_ids[$actor_type];
					$x_label = t('Actor Type');
				}else{
					$y_legend = t("Actors");
					$x_label = t('Type');
				}
				$title = get_actors_by_ethnicity($chart_data, $chart_labels, $term_ids);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Ethicity');
				break;
			case 4://Political affiliation
				if($actor_type){
					$term_ids = truncate_array($term_ids, $actor_type);
					$y_legend = $term_ids[$actor_type];
					$x_label = t('Actor Type');
				}else{
					$y_legend = t("Actors");
					$x_label = t('Type');
				}
				$title = get_actors_by_affiliation($chart_data, $chart_labels, $term_ids);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Pollitical Affiliation');
				break;
				
			case 5://Age
				if($actor_type){
					$term_ids = truncate_array($term_ids, $actor_type);
					$y_legend = $term_ids[$actor_type];
					$x_label = t('Actor Type');
				}else{
					$y_legend = t("Actors");
					$x_label = t('Type');
				}
				$title = get_actors_by_age($chart_data, $chart_labels, $term_ids);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Age');
				break;
			
		}//end switch
	}else if($case_stats_flag){//HANDLE CASE SELECTIONS
		if($case_loc_flag) {
      $case_option = 'location';
      $flag = $case_loc_flag;
    } else {
      $case_option = 'status';
      $flag = $case_status_flag;
    }
		switch($case_stats_flag){
			case 1://Status
				$x_label = t('Status');
				$y_legend = t('Cases');
				$title = get_cases_by_status($chart_data, $chart_labels, $flag);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Status');
				break;
			case 2://Reason for Intervention
				$x_label = t('Reason for Intervention');
				$y_legend = t('Cases');
				$title = get_cases_by_reason($chart_data, $chart_labels, $flag);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Reason for Intervention');
				break;
			case 3://Date of Intervention
				$title = t('Cases by Date of Intervention');
				$y_legend = t('Cases');
				$x_label = t('Month');
				$title = get_cases_by_date($chart_data, $chart_labels, $flag);
				return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Cases');
				break;
			case 4:// Location
				$title = t('Cases by Location');
				$y_legend = t('Cases');
				$case_data_array = get_cases_by_location($chart_data, $chart_labels);
				break;
		}
	}else if($vio_stats_flag){
		$y_legend = t('Violations');
		switch ($vio_stats_flag){
		case 1:
			$x_label = t('Case Names');
			$title = get_violations_by_case($chart_data, $chart_labels, $vio_loc_flag);
			return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Violations');
			break;
		case 2:
			$x_label = t('Month');
			$title = get_violations_by_date($chart_data, $chart_labels, $vio_loc_flag, 1);
			return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Violations');
			break;
		case 3:
			$x_label = t('Year');
			$title = get_violations_by_date($chart_data, $chart_labels, $vio_loc_flag);
			return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Violations');
			break;
		case 4:
			$x_label = t('Standard');
			$title = get_violations_by_standard($chart_data, $chart_labels, $vio_loc_flag);
			return correlative_bar_chart($chart_data, $chart_labels, $title, $x_label ,$y_legend, 'Violations');
			break;
			
		}
			
	}
	
	
}




/*********************************** LEGISLATION CHART ***************************************************/
function get_cases_by_legislation($view_type) {
	$cases_age = array();
	$index = 0;
	$i=0;
	$view = views_get_view($view_type);
	$view->set_items_per_page(ITEMS_PER_PAGE);
	$view->execute();
	if (count($view->result)) {
		foreach ($view->result as $violation) {
			if(($index=check_exists($cases_age, $violation->term_data_tid))==-1){
					$cases_age[$i]['label'] = $violation->term_data_name;
					$cases_age[$i]['id'] = $violation->term_data_tid;
					$cases_age[$i]['num_cases']++;
					$i++;
				}else{
					$cases_age[$index]['num_cases']++;
			}
			
			}
	}
	
	return $cases_age;
}
/*********************************************************************************************************/

/*********************************** VIOLATION CHART ***************************************************/

function get_cases_by_violation($view_type) {
	$cases_age = array();
	$index = 0;
	$i=0;
	$view = views_get_view($view_type);
	$view->set_items_per_page(ITEMS_PER_PAGE);
	$view->execute();
	if (count($view->result)) {
		foreach ($view->result as $violation) {
			$node = node_load($violation->nid);
			$term = load_taxonomy_term($node->taxonomy, 6);
			if(($index=check_exists($cases_age, $term->tid))==-1){
					$cases_age[$i]['label'] = $term->name;
					$cases_age[$i]['id'] = $term->tid;
					$cases_age[$i]['num_cases']++;
					$i++;
				}else{
					$cases_age[$index]['num_cases']++;
			}
			
			}
	}
	
	return $cases_age;
}

/*******************************************************************************************************/

/*********************************** CASES STATUS CHART ************************************************/

function get_cases_by_status(&$chart_data, &$chart_labels, $case_loc_flag){
	$numcases_array = array();
	$i=0;
	global $user;
	
	$tree = taxonomy_get_tree(CASESTATUS);
	
	foreach ($tree as $term) {
	  if( $term->parents[0] === '0' ){//check for top-level element
		  $view = views_get_view('status_stats');
		  $view->set_items_per_page(ITEMS_PER_PAGE);
      /*
		  if($case_loc_flag) {
        $view->args = array("$term->tid, $case_loc_flag", max(array_keys($user->roles)));
		  } else {
        $view->args = array($term->tid, max(array_keys($user->roles)));
      }
      */
      if($case_loc_flag) {
        $view->args = array($term->tid, $case_loc_flag);
      } else {
        $view->args = array($term->tid);
      }
		  $view->execute();
		  if (count($view->result)) {
			  $numcases_array[$i] = count($view->result);
			  $chart_labels[$i] = $term->name;
			  $i++;
		  }
		}
	}
	$chart_data[0]=array(
		'data' => $numcases_array,
		'legend'=>t('Cases')
  );
	
	
	
	$title = t('Cases by Status');
	if($case_loc_flag){
		$title.=' ('.taxonomy_get_term($case_loc_flag)->name.')';
	}	
	return $title;
}
/*********************************************************************************************************/

/*********************************** CASES LOCATION CHART **********************************************/
function get_cases_by_location($location){
	$cases_age = array();
	$view = views_get_view('location_stats');
  $view->set_items_per_page(ITEMS_PER_PAGE);
  
  if($location) {
    $view->set_arguments( array("$location") );
  }
	
	$view->execute();
	$i=0;
	if (count($view->result)) {
		if($location){
			foreach ($view->result as $case) {
				if ($index = check_exists($cases_age, $case->term_data_tid)==-1) {
					$cases_age[$i]['label'] = $case->term_data_name;
					$cases_age[$i]['id'] = $case->term_data_tid;
					$cases_age[$i]['num_cases']++;
					$i++;
				}else{
					$cases_age[$index]['num_cases']++;
				}
			}
		}else{
			foreach ($view->result as $case) {
				$parent = taxonomy_get_parents($case->term_data_tid);
				$pid = get_parent_id($parent);
				$index = check_exists($cases_age, $parent[$pid]->tid);
				if($pid){
				if ($index==-1) {
					$cases_age[$i]['label'] = $parent[$pid]->name;
					$cases_age[$i]['id'] = $parent[$pid]->tid;
					$cases_age[$i]['num_cases']++;
					$i++;
				}else{
					$cases_age[$index]['num_cases']++;
				}
				}
			}
		}
	}
	return $cases_age;
}


/*******************************************************************************************************/

/*********************************** CASES BY REASON FOR INTERVENTION **********************************/

function get_cases_by_reason(&$chart_data, &$chart_labels, $case_loc_flag){
	$numcases_array = array();
	$i=0;
	global $user;
	
	$tree = taxonomy_get_tree(INTERVENTION);
	foreach ($tree as $term) {
		$view = views_get_view('reason_stats');
    /*
		if($case_loc_flag) {
      $view->args = array("$term->tid,$case_loc_flag", max(array_keys($user->roles)));
		} else {
      $view->args = array($term->tid, max(array_keys($user->roles)));
		}
    */
		if($case_loc_flag) {
      $view->args = array($term->tid, $case_loc_flag);
    } else {
      $view->args = array($term->tid);
    }
    $view->set_items_per_page(ITEMS_PER_PAGE);
		$view->execute();
		if (count($view->result)) {
			$numcases_array[$i] = count($view->result);
			$chart_labels[$i] = $term->name;
			$i++;
		}
	}
	$chart_data[0]=array(
		'data' => $numcases_array,
		'legend'=>t('Male'),
		);
	
	
	
	$title = t('Cases by Reason for Intervention');
	if($case_loc_flag){
		$title.=' ('.taxonomy_get_term($case_loc_flag)->name.')';
	}	
	return $title;
	
}

/*******************************************************************************************************/

/*********************************** CASES BY DATE *****************************************************/
/******************************* CASES DATE ***************************************************************/
function get_cases_by_date(&$chart_data, &$chart_labels, $case_flag){
	$i=0;
	$arguments = get_last_twelve_months();
	$numcases_array = array();
	global $user;
	foreach ($arguments as $date_arg => $label) {
		$view = views_get_view('case_date_stats_2');
		// $view->args = array($date_arg, max(array_keys($user->roles)), $case_flag);
		if ($case_flag) {
      $view->args = array($date_arg, $case_flag );
    } else {
      $view->args = array($date_arg);
    }
		
    $view->set_items_per_page( ITEMS_PER_PAGE);
		$view->execute();
   	
    $count_results = count($view->result);
    if($count_results){
			$numcases_array[$i] = $count_results;
			$chart_labels[$i] = $label;
			$i++;
		}
	}
	
	$chart_data[0]=array(
			'data' => $numcases_array,
			'legend'=>t('amount')
  );
	$title = t('Cases by Date');
	if($case_flag){
		$title.=' ('.taxonomy_get_term($case_flag)->name.')';
	}	
	return $title;
}


/*******************************************************************************************************/

/*********************************** ACTORS BY TYPE ****************************************************/


/************************** ACTORS BY TYPE CHART *********************************************************/
function get_actors_by_type(&$chart_data, &$chart_labels, $term_ids){
	$i=0;
	$stats_array = array();
	global $user;
 	foreach ($term_ids as $tid=>$label){
 		$view = views_get_view('actor_type_stats');
		$view->args = array($tid, max(array_keys($user->roles)));

		//$view->args = array($tid);
		$view->set_items_per_page(ITEMS_PER_PAGE);
		$view->execute();
		
		if(count($view->result)){
			$chart_labels[$i] = $label;
			$stats_array[$i] = count($view->result);
      $i++;
		}
	}
	$chart_data[0]=array(
		'data' => $stats_array,
		'legend'=>t('Type')
	);
	
	return t('Actors by Type');
	
}

/*******************************************************************************************************/

/*********************************** ACTORS BY GENDER **************************************************/

function get_actors_by_gender(&$chart_data, &$chart_labels, $term_ids){
	$f_stats_array = array();
	$m_stats_array = array();
	$i=0;
  global $user;
        
	foreach ($term_ids as $tid => $label){
		$fview = views_get_view('gender_stats');
		$mview = views_get_view('gender_stats');
		$fview->args = array("$tid", "female", max(array_keys($user->roles)));
		$mview->args = array("$tid", "male", max(array_keys($user->roles)));
		//$fview->args = array("$tid", "female");
		//$mview->args = array("$tid", "male");
		$fview->set_items_per_page(ITEMS_PER_PAGE);
		$mview->set_items_per_page(ITEMS_PER_PAGE);
		$fview->execute();
		$mview->execute();
		
		if(count($mview->result)||count($fview->result)){
			$f_stats_array[$i] = count($fview->result);
			$m_stats_array[$i] = count($mview->result);
			$chart_labels[$i] = $label;
			$i++;
		}
	}
	$chart_data[0]=array(
		'data' => $m_stats_array,
		'legend'=> t('Male')
	);
	
	$chart_data[1]=array(
		'data' => $f_stats_array,
		'legend' => t('Female') 
	);
	
	
	
	return t('Actors by gender');
}
/*********************************************************************************************************/


/*********************************** ACTOR AGE CHART *****************************************************/

function get_actors_by_age(&$chart_data, &$chart_labels, $term_ids){
	$i=0;
	$age_array = array();
	$labels = array();
	global $user;
	//dpm($term_ids);
	foreach ($term_ids as $tid=> $label) {
		$age_range = array();
		$view = views_get_view('age_stats');
		$view->args = array($tid, max(array_keys($user->roles)));
		//$view->args = array($tid);
		$view->set_items_per_page(ITEMS_PER_PAGE);
		$view->execute();
		if (count($view->result)) {
			foreach ($view->result as $actor) {
			$age = $actor->node_data_field_age_field_age_value;
				switch($age){
					case 0:
					case $age<= 18:
						$age_range['0-18']++;
						break;
					case $age<= 35:
						$age_range['18-35']++;
						break;
					case $age<= 50:
						$age_range['35-50']++;
						break;
					case $age> 50:
						$age_range['50+']++;
						break;		
				}// end switch
			}// end inner for each
		}// end if
		$age_array[0][$i] = $age_range['0-18'];
		$age_array[1][$i] = $age_range['18-35'];
		$age_array[2][$i] = $age_range['35-50'];
		$age_array[3][$i] = $age_range['50+'];
		$chart_labels[$i] = $label;
		$i++;
	}
	$i=0;
	$labels = array("0-18", "18-35", "35-50", "50+");
	foreach ($age_array as $age){
		$chart_data[$i]=array(
		'data' => $age,
		'legend'=>$labels[$i]);
		$i++;
	}
	
	
	return t('Actors by Age');

}
/*********************************************************************************************************/


/********************************** ACTOR ETHNICITY CHART ************************************************/
function get_actors_by_ethnicity(&$chart_data, &$chart_labels, $term_ids){
	$s_stats_array = array();//17
	$n_stats_array = array();//46
	$o_stats_array = array();//59
	global $user;
	foreach ($term_ids as $tid=> $label) {
		$sview = views_get_view('ethnicity_stats');
		$sview->set_items_per_page(ITEMS_PER_PAGE);
		$nview = views_get_view('ethnicity_stats');
		$nview->set_items_per_page(ITEMS_PER_PAGE);
		$oview = views_get_view('ethnicity_stats');
		$oview->set_items_per_page(ITEMS_PER_PAGE);
		$sview->args = array($tid, "17", max(array_keys($user->roles)));
		$nview->args = array($tid, "46", max(array_keys($user->roles)));
		$oview->args = array($tid, "59", max(array_keys($user->roles)));
		//$sview->args = array($tid, "17" );
		//$nview->args = array($tid, "46" );
		//$oview->args = array($tid, "59" );
		$sview->execute();
		$nview->execute();
		$oview->execute();
		if(count($sview->result)||count($nview->result)||count($oview->result)){
			$s_stats_array[$i] = count($sview->result);
			$n_stats_array[$i] = count($nview->result);
			$o_stats_array[$i] = count($oview->result);
			
			$chart_labels[$i] = $label;
			$i++;
		}
		
	}
	$chart_data[0]=array(
		'data' => $s_stats_array,
		'legend'=>'Shona');
	
	$chart_data[1]=array(
		'data' => $n_stats_array,
		'legend'=>'Ndebele');
	
	$chart_data[2]=array(
		'data' => $o_stats_array,
		'legend'=>'Other');
	
	return t('Actors by Ethnicity');
}



/*******************************************************************************************************/


/*********************************** ACTOR BY AFFILIATION **********************************************/

function get_actors_by_affiliation(&$chart_data, &$chart_labels, $term_ids){
  
  
  
  
	$i=0;$j=0;
	$tree = taxonomy_get_tree(AFFILIATION);
	foreach($tree as $term){
		$each_array = array();
		global $user;
		foreach ($term_ids as $tid=> $label) {
			//$view = views_get_view('political_affiliation_stats');
			$view = views_get_view('political_affiliation');
			$view->args = array($tid, max(array_keys($user->roles)));
			//$view->args = array("$tid,$term->tid" );
			$view->set_items_per_page(ITEMS_PER_PAGE);
			$view->execute();
			$num_actors = count($view->result);
			if(count($view->result))$total = count($view->result);
			else $total = 0;
			$each_array[$j] = $total;
			$j++;
		}
		$chart_data[$i]=array(
		'data' => $each_array,
		'legend'=>$term->name);
		$i++;
	}
	if(count($term_ids)>1)$chart_labels = array( t('Perpetrators'), t('Victims'), t('Witnesses'));
	else $chart_labels = array($label);
	
	return t('Actors by Political Affiliation');
}



/*******************************************************************************************************/

/*********************************** VIOLATIONS BY CASE ************************************************/
function get_violations_by_case(&$chart_data, &$chart_labels, $vio_loc_flag){
	$i=0;
	$case_num_array = array();
	$view_cases = views_get_view('case_date_stats');
	$view_cases->set_items_per_page(ITEMS_PER_PAGE);
	$view_cases->execute();
	global $user;
	foreach ($view_cases->result as $result){
		$view = views_get_view('violation_stats');
		$view->set_items_per_page(ITEMS_PER_PAGE);
                if($vio_loc_flag){
                   $view->args = array($result->nid, max(array_keys($user->roles)), $vio_loc_flag);
										//$view->args = array($result->nid, $vio_loc_flag);
                }else $view->args = array($result->nid, max(array_keys($user->roles)));
								//$view->args = array($result->nid);
		
		$view->execute();
                if(count($view->result)){
		$case_num_array[$i] = count($view->result);
		$chart_labels[$i] = $result->node_title;
		$i++;
                }
	}
	$chart_data[0]=array(
		'data' => $case_num_array,
		'legend'=>t('Violations'),
	);
		$i++;
	$title = t('Violations by Case');
	if($vio_loc_flag){
		$title.=' ('.taxonomy_get_term($vio_loc_flag)->name.')';
	}	
	return $title;
}

/*******************************************************************************************************/

/*********************************** VIOLATIONS BY DATE(MONTH+YEAR) ************************************/
function get_violations_by_date(&$chart_data, &$chart_labels, $vio_loc_flag, $flag = 0){
	$i=0;
	$data_label = t('year');
	global $user;
	if($flag){
		$date_args = get_last_twelve_months();
		$data_label = t('month');
	}
	else $date_args = get_last_three_years();
	$num_vios_array = array();
	foreach ($date_args as $date_arg => $label) {
		$view = views_get_view('violation_date_stats');
		$view->set_items_per_page(ITEMS_PER_PAGE);
		if($vio_loc_flag)$view->args = array($date_arg, max(array_keys($user->roles)), $vio_loc_flag);
                else $view->args = array($date_arg, max(array_keys($user->roles)));
		$view->execute();
		if(count($view->result)){
			$num_vios_array[$i] = count($view->result);
			$chart_labels[$i] = $label;
			$i++;
		}
	}
	$chart_data[0]=array(
			'data' => $num_vios_array,
			'legend'=>t('amount')
	);
	$title = t('Violations by Date').'('.$data_label.')';
	if($vio_loc_flag)$title.= ' ('.taxonomy_get_term($vio_loc_flag)->name.')';
	return $title;
}
/*******************************************************************************************************/
function get_violations_by_standard(&$chart_data, &$chart_labels, $vio_loc_flag){
	$i=0;
	$tree = taxonomy_get_tree(INTERNATIONALLAW);
	$each_array = array();
	$labels = array();
	global $user;
	foreach($tree as $term){
		$view = views_get_view('violatin_standard_stats');
		if($vio_loc_flag)$view->args = array("$term->tid,$vio_loc_flag", max(array_keys($user->roles)));
                else $view->args = array($term->tid, max(array_keys($user->roles)));
    $view->set_items_per_page(ITEMS_PER_PAGE);
		$view->execute();
		if(count($view->result)){
			$labels[$i] = $term->name;
			$num_vios = count($view->result);
			$each_array[$i] = $num_vios;
			$i++;
		}
	}
	$i=0;
	foreach ($each_array as $data) {
		$chart_data[$i] = array(
			'data'=>array($data),
			'legend' => $labels[$i]
		); 
		$i++;
	}
	/*$chart_data[0]=array(
		'data' => $each_array,
		'legend'=>t('International Standard'));
		*/
	$title = t('Violations by International Standard');
	if($vio_loc_flag)$title.= ' ('.taxonomy_get_term($vio_loc_flag)->name.')';
	return $title;
}



/*********************************** ARRAY PARSING *****************************************************/

function parse_data($case_data) {
	$i=0;
	$num_case = array();
	foreach ($case_data as $num_cases) {
		$num_case[$i] = $num_cases['num_cases'];
		$i++;
	}
	return $num_case;
}


function parse_data_labels($case_data) {
	$i=0;
	$label = array();
	foreach ($case_data as $num_cases) {
		$label[$i] = $num_cases['label'];
		$i++;
	}
	return $label;
}


function check_exists($cases_age, $term_id) {
	$i=0;
	foreach ($cases_age as $case) {
		if ($case['id']==$term_id)return $i;
		$i++;
	}
	return -1;
}

/*********************************************************************************************************/


/************************************* DATE FUNCTIONS ****************************************************/
/**
 * gets an associative array with arguments compatible with views for the last 12 months
 * key returned is the argument, values, its label for the graph
 * @return unknown_type
 */
function get_last_twelve_months(){
	// $months = array('January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December');
	$months = array('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec');

  $arg = array();
	$year = date('Y');
	$month = date('m');
	for($i=$month; $i>$month-12; $i--){
		$argyear = $year;
		$argmonth = $i;
		if($i<1){
			$argyear--;
			$argmonth = 12+$i;
		}
		$arg[$argyear.'-'.$argmonth] = $months[$argmonth-1].' '.$argyear;
	}
	$arg = array_reverse($arg);
	return $arg;
}

function get_last_three_years(){
	$year = date('Y');
	$arg = array();
	for($i=2;$i>-1;$i--){
		$argyear = $year - $i;
		$arg[$argyear] = $argyear;
	}
	return $arg;
}


/*********************************** LOCATION FUNCTION *************************************************************************/
function get_taxonomy($taxonomy_id){
	$tree = taxonomy_get_tree($taxonomy_id, 0, -1, 1);
	$locations = array();
	$locations[0] = t('<select>');
	foreach ($tree as $term) {
		$locations[$term->tid] = $term->name;
	}
	return $locations;
}
