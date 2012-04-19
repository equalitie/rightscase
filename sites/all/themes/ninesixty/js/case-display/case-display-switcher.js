/**
 * @author cormac1
 */
$(document).ready(function(){
	var url = top.window.location.href;
	var flag = 0;
	$('#right-internal-case').hide('fast');
	$('#right-report-case').hide('fast');
	
	
	if (url.search("report")!=-1) {
		//alert("report");
		$('#right-internal-case').hide('fast');
		$('.plan').hide('fast');
		$('.plan-content').hide('fast');
		$('#right-case-details-case').fadeOut('fast', function(){
				$('#right-report-case').fadeIn('fast');
			});
	}
	
	
	
});
