<?php

include_once 'accessors.php';

function sortTable(&$table, $sortName) {
    $sorter=array();
    $ret=array();
    reset($table);
    foreach ($table as $ii => $va) {
        $sorter[$ii]=$va[$sortName  ];
    }
    asort($sorter);
    foreach ($sorter as $ii => $va) {
        $ret[$ii]=$table[$ii];
    }
    $table = $ret;
}

function addDistance(&$games) {
    $myCityId = getMyCityId();
    $gamesNumber = count($games);
    $distances = getCitiesDistances();

    for ($i = 0; $i < $gamesNumber; $i++) {
        $games[$i]['distance'] = round($distances[$games[$i]['city_id']][$myCityId], 0) . ' km';
    }
}

function calculateAttraction($game, $teamsNumber, $distance) {
    $positionWeight = 1.0;
    $awayGameFraction = 0.5;
    $distanceWeight = 1.0;
    $myClubWeight = 1.0;


    $myCityId = getMyCityId();
    $myTeamId = getMyTeamId();

    $numerator = 0.0;
    $denominator = 0.0;

    if ($myTeamId != -1) {
        $denominator += $myClubWeight;
        if ($game['host_id'] == $myTeamId || $game['guest_id'] == $myTeamId) {
            $numerator += $myClubWeight;
        }
    }

    if ($myCityId != -1) {
        $denominator += $distanceWeight;
        if ($game['city_id'] == $myCityId) {
            $numerator += $distanceWeight;
        } else {
            $numerator += ($awayGameFraction * (600.0 - $distance)) / 600.0;
        }
    }

    $teamsPositions = getTeamsPositions();
    $sum = $teamsPositions[$game['host_id']] + $teamsPositions[$game['guest_id']];
    $sum = ((2 * $teamsNumber + 1) - $sum) /  (2 * $teamsNumber - 1);
    $sum *= $positionWeight;
    $numerator += $sum;
    $denominator += $positionWeight;

    return round($numerator / $denominator, 3);
}

function addAttraction($games) {
    $gamesNumber = count($games);
    $teamsNumber = getTeamsNumber();
    $distances = getCitiesDistances();
    $myCityId = getMyCityId();

    for ($i = 0; $i < $gamesNumber; $i++) {
        $distance = 0;
        if ($myCityId != -1) $distance = $distances[$myCityId][$games[$i]['city_id']];
        $games[$i]['attraction'] = calculateAttraction($games[$i], $teamsNumber, $distance);
    }

    return $games;
}