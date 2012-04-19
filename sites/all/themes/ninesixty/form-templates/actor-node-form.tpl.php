
<?php
drupal_add_js("sites/all/themes/ninesixty/js/forms/click-limiter.js");
drupal_add_css("sites/all/themes/ninesixty/styles/forms/forms.css");
$destination = $_GET['destination'];
$vars = explode('/', $destination);
$url_arr = explode('/', $_SERVER['REDIRECT_URL']);
if(strstr($_SERVER['REDIRECT_URL'], 'add'))$prefix = ucfirst($url_arr[2]);
else $prefix = ucfirst($url_arr[3]);
//dpm( $form );

if($vars[3])$type = $vars[3];
else {
    $type = 'victim';

} 
$value=1;
switch($vars[3]) {
    case 'perpetrator':
        $value = 2;
        break;
    case 'applicant':
        $value = 6;
        break;
    case 'witness':
        $value = 3;
        break;
}
drupal_add_js('
			$(document).ready(function(){
				$(\'#edit-taxonomy-1\').val("'.$value.'");
			});
		', 'inline');

?>

<form action="<?php print $form['#action']; ?>" method="post"></form>
<div class="clear-block"></div>
<div class="case-node-form grid-16 container">
    <div class="add-label"><h6><?php print $prefix.' '.ucfirst($type); ?></h6></div>
    <div class="left-form-container grid-8 alpha">
        <div id="case-details-form-left">
            <div class = "form-case" style="display:none">
                <?php

                print drupal_render($form['field_case']);
                drupal_add_js('
						$(document).ready(function(){
							$(\'#edit-field-case-nid-nid\').val("'.$vars[1].'");
						});
					', 'inline');
                ?>

            </div>

            <div class = "form-role" style="display:none">
                <?php

                print drupal_render($form['taxonomy'][1]); ?>

            </div>
            <div class = "form-title left-case input-text">
                <?php print drupal_render($form['field_actor_name']); ?>
                <div class="form-clear" ></div>
            </div>
            
            <div class = "form-gender left-case">
                <?php print drupal_render($form['field_gender']); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-gender left-case">
                <?php print drupal_render($form['taxonomy'][14]); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-dob left-case">
                <?php print drupal_render($form['field_actor_id_number']); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-dob left-case">
                <?php print drupal_render($form['field_dob']); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-dob left-case">
                <?php print drupal_render($form['field_date_death']); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-phone left-case input-text">
                <?php print drupal_render($form['field_contact_details']); ?>
                <div class="form-clear" ></div>
            </div>

            <div class = "form-occupation left-case input-text">
                <?php print drupal_render($form['field_occupation']); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-phone left-case">
                <?php print drupal_render($form['taxonomy'][9]); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-phone left-case">
                <?php print drupal_render($form['taxonomy'][10]); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-phone left-case">
                <?php print drupal_render($form['taxonomy'][11]); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-actor-ethnicity left-case">
                <?php print drupal_render($form['taxonomy'][4]); ?>
                <div class="form-clear" ></div>
            </div>
            <?php if($type=='victim'):?>
                <div class = "form-photo">
                <?php print drupal_render($form['field_outcome']); ?>
                <div class="form-clear" ></div>
            </div>
            <?php endif; ?>
            <div class = "form-photo">
                <?php print drupal_render($form['field_actor_photo']); ?>
                <div class="form-clear" ></div>
            </div>
            <div class = "form-group">
                <?php
                global $user;
                $grps = drupal_render($form['og_nodeapi']);
                if(sizeof($user->og_groups)>1) {
                    print $grps;
                }  ?>
            </div>

        </div>

    </div>
    <div class="right-form-container grid-7 omega">
        <div id="case-details-form-right">
            <?php //if($value!=2): ?>
            <div class="form-testimony">
                <?php print drupal_render($form['body_field']); ?>
            </div>
            <?php //endif; ?>
            <div class="form-files">
                <?php
                print drupal_render($form['field_actor_files']); ?>
            </div>

        </div>

    </div>

</div>
<div class="report-field alpha grid-16">
    <div id="report-field">
        <?php print drupal_render($form['field_report']); ?>
    </div>
</div>

<div class="hide-field alpha grid-16" style="display:none;">
    <?php /* assign the buttons to a variable */
    $buttons = drupal_render($form['buttons']);

    /* print the rest of the form, which will be without buttons because we have already 'printed'
* them when assigning them to the variable, and print the variable right after
* the rest of the form
    */
    print drupal_render($form);
    ?>
</div>
<div class="report-field grid-16">
    <?php print $buttons; ?>

</div>

