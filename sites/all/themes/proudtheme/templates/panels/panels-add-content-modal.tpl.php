<?php
/**
 * @file
 * Template to control the add content modal.
 */
?>
<div class="panels-add-content-modal row">
  <div class="panels-section-column panels-section-column-categories col-md-3">

    <ul class="nav in">
      <?php foreach ($categories_array as $category): ?>
        <li><?php print $category; ?></li>
      <?php endforeach; ?>
    </ul>

  </div>

  <?php print $messages; ?>

  <?php if (!empty($content)): ?>
  <div class="panels-section-columns col-md-9">
    <div class="card-columns card-columns-sm-3 card-columns-md-4 card-columns-xs-2">
      <?php foreach ($content as $id => $item): ?>

        <?php print $item['rendered']; ?>

      <?php endforeach; ?>
    </div>
  </div>
  <?php endif; ?>
</div>
