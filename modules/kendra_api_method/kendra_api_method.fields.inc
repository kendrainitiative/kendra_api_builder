<?php

/**
 * computed field : rest_request : compute

 * @param unknown_type $node
 * @param unknown_type $field
 * @param unknown_type $node_field
 */
function computed_field_field_rest_request_computed_compute(&$node, $field, &$node_field) {
	$url = KENDRA_API_ENDPOINT_BASE . KENDRA_API_ENDPOINT_PATH_PREFIX . $node->field_rest_uri_fragment[0]['value'];
	$method = $node->field_rest_http_method[0]['value'];
	$data = array();

	$my_tokens = array(
    'curl'
    ,'-v'
    ,'-H "Content-Type: application/json"'
    ,'-X ' . $method
    );
	$placeholders = array('foo','bar','baz','qux');

    if ($method == 'GET') {
    	foreach($node->field_method_params as $i => $param) {
    		// var_dump($param);
	  $data[] = urlencode($param['value'] . '=' . next($placeholders));
    	}

    	$url .= join('&', $data);

    } else if ($method == 'POST' || $method == 'PUT' || $method == 'DELETE') {
    	foreach($node->field_method_params as $i => $param) {
    		// var_dump($param);
	  $data[] = urlencode($param['value'] . '=' . next($placeholders));
    	}

    	if (!empty($data)) {
    		$my_tokens[] = sprintf('--data "%s"', join('&', $data));
    	}
    }

    $my_tokens[] = $url;
    $node_field[0]['value'] = join(' ', $my_tokens);
}

/**
 * computed field: test_url_computed_compute
 *
 * @param $node
 * @param $field
 * @param $node_field
 */
function computed_field_field_test_url_computed_compute(&$node, $field, &$node_field) {
	$url = KENDRA_API_ENDPOINT_BASE . '?';
	$url_path_prefix = KENDRA_API_ENDPOINT_PATH_PREFIX;
	$data = array();
	$placeholders = array('foo','bar','baz','qux');

	foreach($node->field_method_params as $i => $param) {
		//var_dump($node->field_method_params[i]);
	  $data[] = $node->field_method_params[i]['value'] . '=' . next($placeholders);
	}

	$url .= join('&',
	array(
        'endpoint_method='.$node->field_rest_http_method[0]['value']
	,'endpoint_path=' . $url_path_prefix . $node->field_rest_uri_fragment[0]['value']
	,'endpoint_data=' . urlencode(join('&', $data))
	));

	$node_field[0]['value'] = $url;
}

/**
 * computed field: rest_request : display
 * @param unknown_type $field
 * @param unknown_type $element
 * @param unknown_type $node
 */
function computed_field_field_rest_request_computed_display($field, $element, $node) {
	$display = $node_field_item['value'];
}

/**
 * computed field: test_url : display
 * @param unknown_type $field
 * @param unknown_type $element
 * @param unknown_type $node
 */
function computed_field_field_test_url_computed_display($field, $element, $node) {
	$url = $node_field_item['value'];
	$display = l($url,$url);
}
