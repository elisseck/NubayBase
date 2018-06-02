
<?php if ($page == 0): ?>

<?php
  $node_obj = node_load($node->nid);

		$box_location = '';
		$box_width = '';
		$box_bg_color = '';
		$text_color = '';
		$font_size = '';
		$title_font_size = '';
		$font_typeface = '';
		if(!empty($node_obj->field_text_box_location)){
		  $box_location = $node_obj->field_text_box_location['und'][0]['value'];
		}
		if(!empty($node_obj->field_text_box_width)){
    $box_width = $node_obj->field_text_box_width['und'][0]['value'].'px';
  }
		if(!empty($node_obj->field_text_box_background_color)){
    $box_bg_color = $node_obj->field_text_box_background_color['und'][0]['rgb'];
  }
		if(!empty($node_obj->field_text_font_color)){
    $text_color = $node_obj->field_text_font_color['und'][0]['rgb'];
  }
		if(!empty($node_obj->field_text_font_size)){
    $font_size = $node_obj->field_text_font_size['und'][0]['value'].'px';
  }
		if(!empty($node_obj->field_text_font_typefaces)){
    $font_typeface = $node_obj->field_text_font_typefaces['und'][0]['value'];
  }
		if(!empty($node_obj->field_title_font_size)){
    $title_font_size = $node_obj->field_title_font_size['und'][0]['value'].'px';
  }

		$text_align = $node_obj->field_text_justify['und'][0]['value'];
?>
<div id="slideshow">
	 <div class="slideshow_img">
	   <?php
			   if(user_access('administer nodes')){
            print "<div class='edit_link'>".l(t('EDIT'),'node/'.$node->nid.'/edit', array('query'=>drupal_get_destination()))."</div>";
      }
			   $image_settings = array(
			   'style_name' => 'slideshow',
			   'path' => $node_obj->field_slider_image['und'][0]['uri'],
			   'attributes' => array('class' => 'image'),
			   'getsize' => TRUE,
			   );
			   $image_path = theme('image_style', $image_settings);
						print $image_path;
    ?>
	 </div>
		
		   <div id="position_<?php print $box_location; ?>" class="slideshow_text" style="width:<?php print $box_width; ?>; font-size:<?php print $font_size; ?>; font-family:<?php print $font_typeface; ?>; background:<?php print $box_bg_color; ?>; color:<?php print $text_color; ?>; text-align:<?php print $text_align; ?>;">
       <div class="position">
							     <div class="slide_title" style="font-size:<?php print $title_font_size; ?>"><?php print $node_obj->title; ?></div>  
												<div class="slide_text">
												<?php 
										  		if(!empty($node_obj->field_text_box)){
												    print $node_obj->field_text_box['und'][0]['value'];
              }
												?>
												</div>
												<div class="link_text"><?php print render($content['field_link_text']); ?></div>
				  	</div>
					</div>
</div>

<!--Caption text for mobile device-->
<div class="mobile_image_text_box_caption">
    <div class="slide_title"><h2>
					<?php   print $node_obj->title;  ?>
				<h2></div>  
				<div class="slide_text">
						<?php 	if(!empty($node_obj->field_text_box)){
									 print $node_obj->field_text_box['und'][0]['value'];
       }	?>
					</div>
				<div class="link_text"><?php print render($content['field_link_text']); ?></div>
</div>
<!--end Caption text-->

<?php else: ?>

<?php

		$box_location = '';
		$box_width = '';
		$box_bg_color = '';
		$text_color = '';
		$font_size = '';
		$title_font_size = '';
		$font_typeface = '';
		if(!empty($node->field_text_box_location)){
		  $box_location = $node->field_text_box_location['und'][0]['value'];
		}
		if(!empty($node->field_text_box_width)){
    $box_width = $node->field_text_box_width['und'][0]['value'].'px';
  }
		if(!empty($node->field_text_box_background_color)){
    $box_bg_color = $node->field_text_box_background_color['und'][0]['rgb'];
  }
		if(!empty($node->field_text_font_color)){
    $text_color = $node->field_text_font_color['und'][0]['rgb'];
  }
		if(!empty($node->field_text_font_size)){
    $font_size = $node->field_text_font_size['und'][0]['value'].'px';
  }
		if(!empty($node->field_text_font_typefaces)){
    $font_typeface = $node->field_text_font_typefaces['und'][0]['value'];
  }
		if(!empty($node->field_title_font_size)){
    $title_font_size = $node->field_title_font_size['und'][0]['value'].'px';
  }

		$text_align = $node->field_text_justify['und'][0]['value'];
?>
<div id="slideshow">
	 <div class="slideshow_img">
	   <?php
			   if(user_access('administer nodes')){
            print "<div class='edit_link'>".l(t('EDIT'),'node/'.$node->nid.'/edit', array('query'=>drupal_get_destination()))."</div>";
      }
			   $image_settings = array(
			   'style_name' => 'slideshow',
			   'path' => $node->field_slider_image['und'][0]['uri'],
			   'attributes' => array('class' => 'image'),
			   'getsize' => TRUE,
			   );
			   $image_path = theme('image_style', $image_settings);
						print $image_path;
    ?>
	 </div>
		
		   <div id="position_<?php print $box_location; ?>" class="slideshow_text" style="width:<?php print $box_width; ?>; font-size:<?php print $font_size; ?>; font-family:<?php print $font_typeface; ?>; background:<?php print $box_bg_color; ?>; color:<?php print $text_color; ?>; text-align:<?php print $text_align; ?>;">
       <div class="position">
							     <div class="slide_title" style="font-size:<?php print $title_font_size; ?>"><?php print $node->title; ?></div>  
												<div class="slide_text">
												<?php 
										  		if(!empty($node->field_text_box)){
												    print $node->field_text_box['und'][0]['value'];
              }
												?>
												</div>
												<div class="link_text"><?php print render($content['field_link_text']); ?></div>
				  	</div>
					</div>

</div>

<!--Caption text for mobile device-->
<div class="mobile_image_text_box_caption">
    <div class="slide_title"><h2>
					<?php   print $node->title;  ?>
				<h2></div>  
				<div class="slide_text">
						<?php 	if(!empty($node->field_text_box)){
									 print $node->field_text_box['und'][0]['value'];
       }	?>
					</div>
				<div class="link_text"><?php print render($content['field_link_text']); ?></div>
</div>
<!--end Caption text-->

<?php endif; ?>
