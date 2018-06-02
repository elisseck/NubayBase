<?php

$item_id = @$variables['elements']['#entity']->item_id;
if(!empty($item_id)){
  $paragraph_obj = paragraphs_item_load($item_id);
		
		$box_location = '';
		$box_width = '';
		$box_bg_color = '';
		$text_color = '';
		$font_size = '';
		$title_font_size = '';
		$font_typeface = '';
		if(!empty($paragraph_obj->field_text_box_location)){
		  $box_location = $paragraph_obj->field_text_box_location['und'][0]['value'];
		}
		if(!empty($paragraph_obj->field_text_box_width)){
    $box_width = $paragraph_obj->field_text_box_width['und'][0]['value'].'px';
  }
		if(!empty($paragraph_obj->field_text_box_background_color)){
    $box_bg_color = $paragraph_obj->field_text_box_background_color['und'][0]['rgb'];
  }
		if(!empty($paragraph_obj->field_text_font_color)){
    $text_color = $paragraph_obj->field_text_font_color['und'][0]['rgb'];
  }
		if(!empty($paragraph_obj->field_text_font_size)){
    $font_size = $paragraph_obj->field_text_font_size['und'][0]['value'].'px';
  }
		if(!empty($paragraph_obj->field_text_font_typefaces)){
    $font_typeface = $paragraph_obj->field_text_font_typefaces['und'][0]['value'];
  }
		if(!empty($paragraph_obj->field_title_font_size)){
    $title_font_size = $paragraph_obj->field_title_font_size['und'][0]['value'].'px';
  }

		$text_align = $paragraph_obj->field_text_justify['und'][0]['value'];
		
?>

<div id="slideshow">
	 <div class="slideshow_img">
	   <?php
			   $image_settings = array(
			   'style_name' => 'slideshow',
			   'path' => $paragraph_obj->field_slider_image['und'][0]['uri'],
			   'attributes' => array('class' => 'image'),
			   'getsize' => TRUE,
			   );
			   $image_path = theme('image_style', $image_settings);
						print $image_path;
    ?>
	 </div>
		
		   <div id="position_<?php print $box_location; ?>" class="slideshow_text" style="width:<?php print $box_width; ?>; font-size:<?php print $font_size; ?>; font-family:<?php print $font_typeface; ?>; background:<?php print $box_bg_color; ?>; color:<?php print $text_color; ?>; text-align:<?php print $text_align; ?>;">
       <div class="position">
							     <div class="slide_title" style="font-size:<?php print $title_font_size; ?>">
												<?php 
												  if(!empty($paragraph_obj->field_s_title)){
											    	print $paragraph_obj->field_s_title['und'][0]['value']; 
														}
												?>
												</div>  
												<div class="slide_text">
												<?php 
										  		if(!empty($paragraph_obj->field_text_box)){
												    print $paragraph_obj->field_text_box['und'][0]['value'];
              }
												?>
												</div>
												<div class="link_text"><?php print render($content['field_link_text']); ?></div>
				  	</div>
					</div>
				


</div>

<div class="mobile_image_text_box_caption">
    <div class="slide_title"><h2>
					<?php  if(!empty($paragraph_obj->field_s_title)){
					   print $paragraph_obj->field_s_title['und'][0]['value']; 
						} ?>
				<h2></div>  
				<div class="slide_text">
						<?php 	if(!empty($paragraph_obj->field_text_box)){
									 print $paragraph_obj->field_text_box['und'][0]['value'];
       }	?>
					</div>
				<div class="link_text"><?php print render($content['field_link_text']); ?></div>
</div>

<?php

}else{
   print render($content);
}

?>