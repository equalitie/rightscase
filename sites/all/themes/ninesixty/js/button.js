/**
 * @author cormac1
 */
$(document).ready(function(){
	var flag=0;
	var color;
	$('.edit-button a').addClass('button').wrapInner('<span></span>');
	$('.odd').children().css("background-color","#ffffff");
	$('.actor-link').parent().parent().click(function(){
		//document.location = this.children(0).attr('href');
		
		if(flag==0){
			$(this).children().css("background-color","#C9E8FF").children().css("background-color","#C9E8FF");
			flag++;
			document.location = ($(this).children('td').children('.actor-link').attr("href"));
		}
		
	});
	$('.actor-link').parent().parent().hover(function(){
		
		if (flag == 0) {
			color = $(this).children().css("background-color");
			
			$(this).children().css("background-color","#daEbFF").children().css("background-color","#daEbFF");
			$(this).siblings('.even').css("background-color","#eeeeee").children().css("background-color","#eeeeee").children().css("background-color","#eeeeee");
			$(this).siblings('.odd').css("background-color","#ffffff").children().css("background-color","#ffffff").children().css("background-color","#ffffff");
			
		}
	});
	
});