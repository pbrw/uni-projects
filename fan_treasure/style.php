<?php
$style = '
<html lang="en">
<head>
<style>
table.blueTable {
  border: 1px solid #1C6EA4;
  background-color: #EEEEEE;
  width: 75%;
  text-align: left;
  border-collapse: collapse;
}
table.blueTable td, table.blueTable th {
  border: 1px solid #AAAAAA;
  padding: 3px 2px;
}
table.blueTable tbody td {
  font-size: 13px;
}

table.blueTable thead {
  background: #1C6EA4;
  background: -moz-linear-gradient(top, #5592bb 0%, #327cad 66%, #1C6EA4 100%);
  background: -webkit-linear-gradient(top, #5592bb 0%, #327cad 66%, #1C6EA4 100%);
  background: linear-gradient(to bottom, #5592bb 0%, #327cad 66%, #1C6EA4 100%);
  border-bottom: 2px solid #444444;
}
table.blueTable thead th {
  font-size: 15px;
  font-weight: bold;
  color: #FFFFFF;
  border-left: 2px solid #D0E4F5;
}
table.blueTable thead th:first-child {
  border-left: none;
}

table.blueTable tfoot {
  font-size: 14px;
  font-weight: bold;
  color: #FFFFFF;
  background: #D0E4F5;
  background: -moz-linear-gradient(top, #dcebf7 0%, #d4e6f6 66%, #D0E4F5 100%);
  background: -webkit-linear-gradient(top, #dcebf7 0%, #d4e6f6 66%, #D0E4F5 100%);
  background: linear-gradient(to bottom, #dcebf7 0%, #d4e6f6 66%, #D0E4F5 100%);
  border-top: 2px solid #444444;
}
table.blueTable tfoot td {
  font-size: 14px;
}
table.blueTable tfoot .links {
  text-align: right;
}
table.blueTable tfoot .links a{
  display: inline-block;
  background: #1C6EA4;
  color: #FFFFFF;
  padding: 2px 8px;
  border-radius: 5px;
}
.myButton {
	-moz-box-shadow: 0px 1px 0px 0px #f0f7fa;
	-webkit-box-shadow: 0px 1px 0px 0px #f0f7fa;
	box-shadow: 0px 1px 0px 0px #f0f7fa;
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #6397cf), color-stop(1, #0277d1));
	background:-moz-linear-gradient(top, #6397cf 5%, #0277d1 100%);
	background:-webkit-linear-gradient(top, #6397cf 5%, #0277d1 100%);
	background:-o-linear-gradient(top, #6397cf 5%, #0277d1 100%);
	background:-ms-linear-gradient(top, #6397cf 5%, #0277d1 100%);
	background:linear-gradient(to bottom, #6397cf 5%, #0277d1 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr=\'#6397cf\', endColorstr=\'#0277d1\',GradientType=0);
	background-color:#6397cf;
	-moz-border-radius:8px;
	-webkit-border-radius:8px;
	border-radius:8px;
	border:1px solid #ffffff;
	display:inline-block;
	cursor:pointer;
	color:#ffffff;
	font-family:Arial;
	font-size:10px;
	font-weight:bold;
	padding:4px 18px;
	text-decoration:none;
	text-shadow:0px -1px 0px #5b6178;
}
.myButton:hover {
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #0277d1), color-stop(1, #6397cf));
	background:-moz-linear-gradient(top, #0277d1 5%, #6397cf 100%);
	background:-webkit-linear-gradient(top, #0277d1 5%, #6397cf 100%);
	background:-o-linear-gradient(top, #0277d1 5%, #6397cf 100%);
	background:-ms-linear-gradient(top, #0277d1 5%, #6397cf 100%);
	background:linear-gradient(to bottom, #0277d1 5%, #6397cf 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr=\'#0277d1\', endColorstr=\'#6397cf\',GradientType=0);
	background-color:#0277d1;
}
.myButton:active {
	position:relative;
	top:1px;
}

.select-style {
    border: 1px solid #ccc;
    width: 120px;
    border-radius: 3px;
    overflow: hidden;
    background: #fafafa url("img/icon-select.png") no-repeat 90% 50%;
}

.select-style select {
    padding: 5px 8px;
    width: 130%;
    border: none;
    box-shadow: none;
    background: transparent;
    background-image: none;
    -webkit-appearance: none;
}

.select-style select:focus {
    outline: none;
}

.enjoy-css {
  -webkit-box-sizing: content-box;
  -moz-box-sizing: content-box;
  box-sizing: content-box;
  width: 100%;
  height: 100%;
  border: none;
  font: normal 16px/1 "Times New Roman", Times, serif;
//  color: rgba(255,255,255,1);
  text-align: center;
  -o-text-overflow: ellipsis;
  text-overflow: ellipsis;
//  background: -webkit-linear-gradient(-90deg, rgba(0,150,255,1) 0, rgba(0,110,255,1) 78%, rgba(255,255,255,1) 100%);
//  background: -moz-linear-gradient(180deg, rgba(0,150,255,1) 0, rgba(0,110,255,1) 78%, rgba(255,255,255,1) 100%);
//  background: linear-gradient(180deg, rgba(0,150,255,1) 0, rgba(0,110,255,1) 78%, rgba(255,255,255,1) 100%);
//  background-position: 50% 50%;
  -webkit-background-origin: padding-box;
  background-origin: padding-box;
  -webkit-background-clip: border-box;
  background-clip: border-box;
  -webkit-background-size: auto auto;
  background-size: auto auto;
}

.cl-effect-15 a {
	color: rgba(0,0,0,0.2);
	font-weight: 700;
	text-shadow: none;
}

.cl-effect-15 a::before {
	color: #fff;
	content: attr(data-hover);
	position: absolute;
	transition: transform 0.3s, opacity 0.3s;
}

.cl-effect-15 a:hover::before,
.cl-effect-15 a:focus::before {
	transform: scale(0.9);
	opacity: 0;
}


</style>
</head>
';

echo $style;