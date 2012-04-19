/**
 * @author cormac1
 * views-cycle-case_actors-page_2
 */
$(document).ready(function(){
	$('#views-cycle-case_actors-page_1-nav').addClass('grid-3');
	$('#views-cycle-case_actors-page_2-nav').addClass('grid-3');
	$('#views-cycle-case_actors-page_3-nav').addClass('grid-3');
	$('#views-cycle-case_actors-page_4-nav').addClass('grid-3');
	$('#views-cycle-case_actors-page_1').addClass('grid-13');
	$('#views-cycle-case_actors-page_2').addClass('grid-13');
	$('#views-cycle-case_actors-page_3').addClass('grid-13');
	$('#views-cycle-case_actors-page_4').addClass('grid-13');
	
	$("#views-cycle-case_actors-page_1-nav").wrap("<div class=\"sideTab actor-tab grid-3 alpha\"></div>");
	$("#views-cycle-case_actors-page_2-nav").wrap("<div class=\"sideTab actor-tab grid-3 alpha\"></div>");
	$("#views-cycle-case_actors-page_3-nav").wrap("<div class=\"sideTab actor-tab grid-3 alpha\"></div>");
	$("#views-cycle-case_actors-page_4-nav").wrap("<div class=\"sideTab actor-tab grid-3 alpha\"></div>");
	
	$("#views-cycle-case_actors-page_1-nav").after('<div class="sideTab-bottom-actor"></div>');
	$("#views-cycle-case_actors-page_2-nav").after('<div class="sideTab-bottom-actor"></div>');
	$("#views-cycle-case_actors-page_3-nav").after('<div class="sideTab-bottom-actor"></div>');
	$("#views-cycle-case_actors-page_4-nav").after('<div class="sideTab-bottom-actor"></div>');
	
	$('.actor-tab').prepend('<div class="sideTabHeader actor-tab-header"><h6>Actors</h6></div>');
	$(".activeSlide").parent().addClass('activeSlide');
	$("li").click(function(){
		$(this).addClass('activeSlide');
		$(this).siblings().removeClass('activeSlide');
	});
	
});
