<?php if ($page == 0): ?>
<?php
//This will work for block/listing pages
  $node_obj = node_load($node->nid);
  
  $block_width = '';
  $block_height = '';
  $title_fontsize = '';
  $title_typeface = '';
  $title_color = '';
  $text_align = '';
  $link_title = '';
  $link_fontsize = '';
  $link_typeface = '';
  $link_color = '';
  $bg_color = '';
  $border_width = '';
  $border_color = '';
  $border_radius = '';
  $parent_padding = '';
  $padding_top = '';
  $padding_right = '';
  $padding_bottom = '';
  $padding_left = '';
  $font_weight = '';
  $block_image = '';
  if(!empty($node_obj->field_block_width)){
    $block_width = $node_obj->field_block_width['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_block_height)){
    $block_height = $node_obj->field_block_height['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_title_text_font_size)){
    $title_fontsize = $node_obj->field_title_text_font_size['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_title_text_font_color)){
    $title_color = $node_obj->field_title_text_font_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_title_text_font_typeface)){
    $title_typeface = $node_obj->field_title_text_font_typeface['und'][0]['value'];
  }
  if(!empty($node_obj->field_cta_link_text)){
    $link_title = $node_obj->field_cta_link_text['und'][0]['value'];
  }
  if(!empty($node_obj->field_link_text_size)){
    $link_fontsize = $node_obj->field_link_text_size['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_link_font_typeface)){
    $link_typeface = $node_obj->field_link_font_typeface['und'][0]['value'];
  }
  if(!empty($node_obj->field_link_text_color)){
    $link_color = $node_obj->field_link_text_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_background_color)){
    $bg_color = $node_obj->field_background_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_border_width)){
    $border_width = $node_obj->field_border_width['und'][0]['value'].'px solid';
  }
  if(!empty($node_obj->field_border_color)){
    $border_color = $node_obj->field_border_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_border_radius)){
    $border_radius = $node_obj->field_border_radius['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_padding)){
    $parent_padding = $node_obj->field_padding['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_top)){
    $padding_top = $node_obj->field_cta_block_padding_top['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_right)){
    $padding_right = $node_obj->field_cta_block_padding_right['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_bottom)){
    $padding_bottom = $node_obj->field_cta_block_padding_bottom['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_left)){
    $padding_left = $node_obj->field_cta_block_padding_left['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_title_align)){
    $text_align = $node_obj->field_title_align['und'][0]['value'];
  }
  if(!empty($node_obj->field_title_font_weight)){
    $font_weight = $node_obj->field_title_font_weight['und'][0]['value'];
  }
  if(!empty($node_obj->field_background_image)){
    $block_image = file_create_url($node_obj->field_background_image['und'][0]['uri']);
  }
?>

<?php if(empty($link_title)){ ?>
  <a href="<?php print $node_obj->field_link_destination['und'][0]['url']; ?>">
<?php } ?>
<?php if(!empty($parent_padding)){ ?>
  <div class="cta_block_parent" style="padding:<?php print $parent_padding; ?>; background:<?php if($block_image){ }else{print $bg_color;} ?>">
<?php } ?>
<div class="cta_block" style="width:<?php print $block_width ?>; height:<?php print $block_height ?>; border:<?php print $border_width.' '.$border_color ?>; background:<?php if($block_image){ print 'url('.$block_image.') no-repeat 0% 0%' ; }else{print $bg_color;} ?>; <?php if($block_image){ ?>background-size: cover; background-origin: content-box;<?php } ?> border-radius:<?php print $border_radius ?>; padding-top:<?php print $padding_top ?>; padding-right:<?php print $padding_right ?>; padding-bottom:<?php print $padding_bottom ?>; padding-left:<?php print $padding_left ?>; text-align:<?php print $text_align ?>;">
<?php if(empty($node_obj->field_hide_title)){ ?>
  <h2 class="block_title" style="font-size:<?php print $title_fontsize ?>; color:<?php print $title_color ?>; font-family:<?php print $title_typeface ?>; font-weight:<?php print $font_weight ?>;"><?php print $node_obj->title; ?></h2>
  <?php } ?>
  <?php if(!empty($link_title)){ ?>
    <span class="cta_link">
	 <a href="<?php print $node_obj->field_link_destination['und'][0]['url'];?>" style="font-size:<?php print $link_fontsize ?>; font-family:<?php print $link_typeface ?>; color:<?php print $link_color ?>;"><?php print $link_title; ?></a>
    </span>
  <?php	} ?>
</div>
<?php if(!empty($padding)){ ?>
  </div>
<?php } ?>
<?php if(empty($link_title)){ ?>
</a>
<?php } ?>



<?php else: ?>



<?php
//This will work for Details pages
 $node_obj = node_load($node->nid);
  
  $block_width = '';
  $block_height = '';
  $title_fontsize = '';
  $title_typeface = '';
  $title_color = '';
  $text_align = '';
  $link_title = '';
  $link_fontsize = '';
  $link_typeface = '';
  $link_color = '';
  $bg_color = '';
  $border_width = '';
  $border_radius = '';
  $border_color = '';
  $parent_padding = '';
  $padding_top = '';
  $padding_right = '';
  $padding_bottom = '';
  $padding_left = '';
  $font_weight = '';
  $block_image = '';
  if(!empty($node_obj->field_block_width)){
    $block_width = $node_obj->field_block_width['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_block_height)){
    $block_height = $node_obj->field_block_height['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_title_text_font_size)){
    $title_fontsize = $node_obj->field_title_text_font_size['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_title_text_font_color)){
    $title_color = $node_obj->field_title_text_font_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_title_text_font_typeface)){
    $title_typeface = $node_obj->field_title_text_font_typeface['und'][0]['value'];
  }
  if(!empty($node_obj->field_cta_link_text)){
    $link_title = $node_obj->field_cta_link_text['und'][0]['value'];
  }
  if(!empty($node_obj->field_link_text_size)){
    $link_fontsize = $node_obj->field_link_text_size['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_link_font_typeface)){
    $link_typeface = $node_obj->field_link_font_typeface['und'][0]['value'];
  }
  if(!empty($node_obj->field_link_text_color)){
    $link_color = $node_obj->field_link_text_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_background_color)){
    $bg_color = $node_obj->field_background_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_border_width)){
    $border_width = $node_obj->field_border_width['und'][0]['value'].'px solid';
  }
  if(!empty($node_obj->field_border_color)){
    $border_color = $node_obj->field_border_color['und'][0]['rgb'];
  }
  if(!empty($node_obj->field_border_radius)){
    $border_radius = $node_obj->field_border_radius['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_padding)){
    $parent_padding = $node_obj->field_padding['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_top)){
    $padding_top = $node_obj->field_cta_block_padding_top['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_right)){
    $padding_right = $node_obj->field_cta_block_padding_right['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_bottom)){
    $padding_bottom = $node_obj->field_cta_block_padding_bottom['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_cta_block_padding_left)){
    $padding_left = $node_obj->field_cta_block_padding_left['und'][0]['value'].'px';
  }
  if(!empty($node_obj->field_title_align)){
    $text_align = $node_obj->field_title_align['und'][0]['value'];
  }
  if(!empty($node_obj->field_title_font_weight)){
    $font_weight = $node_obj->field_title_font_weight['und'][0]['value'];
  }
  if(!empty($node_obj->field_background_image)){
    $block_image = file_create_url($node_obj->field_background_image['und'][0]['uri']);
  }
?>

<?php if(empty($link_title)){ ?>
  <a href="<?php print $node_obj->field_link_destination['und'][0]['url'];?>">
<?php } ?>
<?php if(!empty($parent_padding)){ ?>
  <div class="cta_block_parent" style="padding:<?php print $parent_padding; ?>; background:<?php if($block_image){ }else{print $bg_color;} ?>">
<?php } ?>
<div class="cta_block_parent" style="padding:5px">
<div class="cta_block" style="width:<?php print $block_width ?>; height:<?php print $block_height ?>; border:<?php print $border_width.' '.$border_color ?>; background:<?php if($block_image){ print 'url('.$block_image.') no-repeat 0% 0%' ; }else{print $bg_color;} ?>; <?php if($block_image){ ?>background-size: cover; background-origin: content-box;<?php } ?> border-radius:<?php print $border_radius ?>; padding-top:<?php print $padding_top ?>; padding-right:<?php print $padding_right ?>; padding-bottom:<?php print $padding_bottom ?>; padding-left:<?php print $padding_left ?>; text-align:<?php print $text_align ?>; font-weight:<?php print $font_weight ?>;">
<?php if(empty($node_obj->field_hide_title)){ ?>
  <h2 class="block_title" style="font-size:<?php print $title_fontsize ?>; color:<?php print $title_color ?>; font-family:<?php print $title_typeface ?>; font-weight:<?php print $font_weight ?>;"><?php print $node_obj->title; ?></h2>
  <?php } ?>
  <?php if(!empty($link_title)){ ?>
    <span class="cta_link">
	 <a href="<?php print $node_obj->field_link_destination['und'][0]['url'];?>" style="font-size:<?php print $link_fontsize ?>; font-family:<?php print $link_typeface ?>; color:<?php print $link_color ?>;"><?php print $link_title; ?> </a>
    </span>
  <?php	} ?>
</div>
<?php if(!empty($parent_padding)){ ?>
  </div>
<?php } ?>
<?php if(empty($link_title)){ ?>
</a>
<?php } ?>


<?php endif; ?>
