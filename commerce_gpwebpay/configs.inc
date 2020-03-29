<?php

function commerce_gpwebpay_api_server_url($server) {
  switch ($server) {
    case 'sandbox':
      return 'https://sandbox.gpwebpay.cz';
    case 'live':
      return 'https://gpwebpay.cz';
  }
}

    

