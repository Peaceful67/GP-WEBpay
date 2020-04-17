<?php

include_once 'settings.inc';

function commerce_gpwebpay_process_ipn() {
    $success = isIPNSucceed();
    $order_id = filter_input(INPUT_POST, 'ORDERNUMBER');
//    $result = filter_input(INPUT_POST, 'RESULTTEXT');
    $order = commerce_order_load($order_id);
    if ($success) {
        $transaction_id = filter_input(INPUT_POST, 'MERORDERNUM');
        $transaction = commerce_payment_transaction_load($transaction_id);
        $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
        $transaction->log = 'Successful payment by GPWEBpay';
        commerce_payment_transaction_save($transaction);
        $order = commerce_order_status_update($order, 'checkout_complete', FALSE, TRUE, 'Paid via GPWEBpay');
        commerce_checkout_complete($order);
    } else {
        $order = commerce_order_status_update($order, 'checkout_pending', FALSE, TRUE, 'GPWEBpay payment failed');
    }
    $target_uri = commerce_checkout_order_uri($order);
    if (is_null($target_uri)) {
        drupal_goto();
    } else {
        drupal_goto($target_uri);
    }
}

function isIPNSucceed() {
    $relative = base_path() . drupal_get_path('module', 'commerce_gpwebpay');
    $base = getcwd() . $relative;
    $sign_data = '';
    if ('CREATE_ORDER' != filter_input(INPUT_POST, 'OPERATION')) {
        return false;
    } else {
        $sign_data .= filter_input(INPUT_POST, 'OPERATION') . '|';
    }
    $order = filter_input(INPUT_POST, 'ORDERNUMBER');
    $sign_data .= $order . '|';

    $transaction_id = filter_input(INPUT_POST, 'MERORDERNUM');
    $sign_data .= $transaction_id . '|';

    if (0 != filter_input(INPUT_POST, 'PRCODE')) {
        return false;
    } else {
        $sign_data .= '0|';
    }

    if (0 != filter_input(INPUT_POST, 'SRCODE')) {
        return false;
    } else {
        $sign_data .= '0|';
    }

    if ('OK' != filter_input(INPUT_POST, 'RESULTTEXT')) {
        return false;
    } else {
        $sign_data .= filter_input(INPUT_POST, 'RESULTTEXT');
    }
    $sign = new CSignature($base . PRIVATE_KEY, variable_get('commerce_gpwebpay_passwd'), commerce_gpwebpay_public_key());
    $digest = filter_input(INPUT_POST, 'DIGEST');
    if (!$sign->verify($sign_data, $digest)) {
        return false;
    }
    $sign_data1 = $sign_data . '|' . variable_get('commerce_gpwebpay_merchant');
    $digest1 = filter_input(INPUT_POST, 'DIGEST1');
    if (!$sign->verify($sign_data1, $digest1)) {
        return false;
    }
    return true;
}

function gpwebpay_transaction() {
    
}
