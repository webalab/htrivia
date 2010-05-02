<?php
include( 'htrivia.defaults.inc' );

function htrivia_admin_settings() {

  // Generate the form - settings applying to all patterns first
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Info'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['info']['htrivia_question_count'] = array(
    '#type' => 'markup',
    '#value' => ''.t('Question Count').': '.htrivia_question_count(),
  );

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulk Import'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['options']['htrivia_csv_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Questions CSV Path'),
    '#size' => 60,
    '#default_value' => variable_get('htrivia_csv_path',HTRIVIA_CSV_PATH),
    '#description' => t('The URL to a csv files with the questions. You need to hit the save button before running the import if this value is changed.'),
  );

  $form['options']['bulk_import'] = array(
    '#type' => 'submit',
    '#value' => t('Bulk Import'),
    '#submit' => array('htrivia_perform_bulk_import'),
    '#weight' => 10,
  );

  $form['questions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Questions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
	$form['questions']['table']=array(
		'#value' => htrivia_question_list_edit(),
	);


  return system_settings_form($form);
}


function htrivia_perform_bulk_import(){
	htrivia_add_question_batch( _htrivia_parse_file() );
}


function htrivia_question_list_edit(){
  $header = array('id',t('Question'), t('Edit'));
	$questions = htrivia_question_list_raw();
	foreach( $questions as $quest) { 
		$row = array();
    $row[] = $quest['id'];
		$row[] = $quest['question'];
		$row[] = $quest['qid'];
    $rows[] = array('data' => $row);
  }


  return theme('table', $header, $rows, array('id' => 'questions'));
}