(*
	In this task we were given a code of the balanced binary search tree in Ocaml. 
	The goal was to modify it and add new functionalities.
*)



(* 
    Author:     Piotr Borowski   
    Reviewer:  Piotr Grabowski  
*)

(* 
    Reprezentacja drzewa przedziałów:
     Node(l, (x, y), r, h, c):
       l - lewe poddrzewo
       x - początek przedziału w wierzchołku
       y - koniec przedziału w wierzchołku
       r - prawe poddrzewo
       h - wysokość drzewa
       c - liczba elementów w drzewie
     Empty - drzewo puste
*) 
type t =
  | Empty
  | Node of t * (int * int) * t * int * int

(* Zwraca wysokość drzewa *)
let height = function
  | Node (_, _, _, h, _) -> h
  | Empty -> 0

(* Zwraca liczbę elementów w drzewie *)
let card = function
  | Node (_, _, _, _, c) -> c
  | Empty -> 0
  
(* 
   Zwraca sumę dwóch liczb z uwzględnieniem 
   przypadków szczególnych dla max_int i min_int 
*)  
let sum x y =
    if x > 0 && y > 0 && x + y < 0 then max_int
    else if x < 0 && y < 0 && x + y > 0 then min_int
    else x + y  

(* Zwraca liczbę liczb w przedziale [x,y] *)
let size x y = 
    sum (sum y (-(sum x 1))) 2

(* Tworzy drzewo z zadanych poddrzew i przedziału *)  	  
let make l (x, y) r = 
    Node( l, (x, y) , r, 
    max (height l) (height r) + 1, 
    sum (sum (card l) (card r)) (size x y))

(* Zwraca puste drzewo *)	
let empty = Empty

(* Sprawdza, czy drzewo jest puste *)
let is_empty x = x = Empty
	
(* Porównuje dwa rozłączne przedziały *)	
let cmp (x, _) (y, _) = compare x y

(* Porównuje przedział i liczbę *)	
let cmp2 (x, y) v =
    if v < x then -1
    else if y < v then 1
    else 0

(* 
   Znajduje przedział, w którym zawiera się 
   liczba x. Zwraca zdegenerowany przedział
   [1,-1], gdy taki przedział nie istnieje 
*)
let rec find x = function
    | Node (l, k, r, _, _) ->
        let c = cmp2 k x in 
        if c = 0 then k 
        else find x (if c < 0 then l else r)
    | Empty -> (1, -1)

(* Sprawdza, czy w zbiorze znajeduje się wartość v *)
let mem v set = 
    let (x, y) = find v set in x <= y

(* Zwraca najmniejszą wartość ze zbioru *)
let rec min_elt = function
    | Node (Empty, k, _, _, _) -> k
    | Node (l, _, _, _, _) -> min_elt l
    | Empty -> raise Not_found

(* Zwraca listę przedziałów w porządku rosnącym *)  
let elements set = 
    let rec loop acc = function
    | Node(l, k, r, _, _) -> loop (k :: loop acc r) l 
    | Empty -> acc in
    loop [] set

(* Wywołuje funkcję f na przedziałach w porządku rosnącym *)
let iter f set =
    let rec loop = function
     | Node (l, k, r, _, _) -> loop l; f k; loop r
     | Empty -> () in
    loop set

(* 
   Oblicza (f xN ... (f x2 (f x1 a))...), gdzie xI to 
   przedziały w porządku rosnącym 
*)
let fold f set acc =
  let rec loop acc = function
    | Node (l, k, r, _, _) ->
          loop (f k (loop acc l)) r
    | Empty -> acc in
  loop acc set

(* Zwraca liczbę elementów niewiększych od v *)
let rec below v = function 
    | Node(l, (x, y), r, _, _) ->
        let res = cmp2 (x, y) v in 
        if res < 0 then below v l
        else if res == 0 then sum (below v l) (size x v)
        else sum (below v r) (sum (card l) (size x y))
    | Empty -> 0

(* 
   Zwraca zbalansowane drzewo BST stworzone z dwóch 
   zbalansowanych drzew BST oraz przedziału niezależnego.
   Przedział k jest większy od przedziałów w zbiorze l 
   i mniejszy od przedziałów w zbiorze r
*)
let bal l k r =
  let hl = height l in
  let hr = height r in
  if hl > hr + 2 then
    match l with
    | Node (ll, lk, lr, _, _) ->
        if height ll >= height lr then make ll lk (make lr k r)
        else
          (match lr with
          | Node (lrl, lrk, lrr, _, _) ->
              make (make ll lk lrl) lrk (make lrr k r)
          | Empty -> assert false)
    | Empty -> assert false
  else if hr > hl + 2 then
    match r with
    | Node (rl, rk, rr, _, _) ->
        if height rr >= height rl then make (make l k rl) rk rr
        else
          (match rl with
          | Node (rll, rlk, rlr, _, _) ->
              make (make l k rll) rlk (make rlr rk rr)
          | Empty -> assert false)
    | Empty -> assert false
  else make l k r

(* 
   Zwraca zbalansowane drzewo BST z dodanym przedziałem [x,y].
   Przedział [x,y] jest niezależny z przedziałami w drzewie.
*)	
let add_dis (x, y) set = 
    if x > y then set
    else let rec add_d v set = 
    match set with
    | Node (l, k, r, _, _) ->
      let res = cmp v k in
      if res = 0 then make l v r
      else if res < 0 then
        let nl = add_d v l in bal nl k r
	  else
		let nr = add_d v r in bal l k nr
    | Empty -> Node (Empty, v, Empty, 1, size x y)
    in add_d (x, y) set

(* 
   Zwraca zbalansowane drzewo BST będące złączeniem
   dwóch zbal. drzew BST oraz przedziału niezależnego
*)
let rec join l v r =
  match (l, r) with
  | (Node(ll, lv, lr, lh, _), Node(rl, rv, rr, rh, _)) ->
      if lh > rh + 2 then bal ll lv (join lr v r) else
      if rh > lh + 2 then bal (join l v rl) rv rr else
      make l v r
  | (Empty, _) -> add_dis v r
  | (_, Empty) -> add_dis v l

(* 
   Zwraca trójkę (l, pres, r), w której l oznacza 
   zbal. drzewo BST z przedziałami mniejszymi od x,
   r oznacza zbal. drzewo BST z przedziałami większymi
   od x, pres jest informacją, czy w drzewie znajdowała
   się wartość x
*) 
let rec split x = function
    | Node (l, v, r, _, _) ->
        let res = cmp2 v x in
        if res = 0 then
          if x = max_int then (add_dis (fst v, x-1) l, true, r)
          else if x = min_int then (l, true, add_dis (x+1, snd v) r)
          else (add_dis (fst v, x-1) l, true, add_dis (x+1, snd v) r)	
        else if res < 0 then
          let (ll, pres, rl) = split x l in (ll, pres, join rl v r)
        else
          let (lr, pres, rr) = split x r in (join l v lr, pres, rr)
    | Empty -> (Empty, false, Empty)

(* Zwraca zbal. drzewo BST bez najmniejszego przedziału *)
let rec remove_min_elt = function
  | Node (Empty, _, r, _, _) -> r
  | Node (l, k, r, _, _) -> bal (remove_min_elt l) k r
  | Empty -> invalid_arg "ISet.remove_min_elt"

(* 
   Zwraca zbal. drzewo BST powstałe z połączenia
   dwóch zbal. drzew BST
*) 
let merge t1 t2 =
  match t1, t2 with
  | Empty, _ -> t2
  | _, Empty -> t1
  | _ -> let k = min_elt t2 in
         bal t1 k (remove_min_elt t2)
(* 
   Zwraca zbal. drzwo BST z usuniętymi 
   wartościami z przedziału [x,y]
*)
let remove (x, y) set = 
    let (ls, _, gt) = split y set in
    let (ls, _, _) = split x ls in
    merge ls gt 

(* 
   Zwraca zbal. drzewo BST z dodanymi 
   wartościami z przedziału [x,y]
*)
let add (x, y) set =
    let (a, b) = find (sum x (-1)) set 
    and (c, d) = find (sum y 1) set
    in let v = (if a <= b then a else x)
       and w = (if c <= d then d else y)
       in add_dis (v, w) (remove (v, w) set)
       
       
(* TESTY *)
      
(*
let s = Empty;;
let s = add (1, 3) s;;
let s = add (-7, -3) s;;
let s = add (5, 10) s;;
let s = add (15, 17) s;;
let s = add (20, 20) s;;

let a1 = below (-1) s;;
assert (a1 = 5);;
let a2 = below 1 s;;
assert (a2 = 6);;
let a3 = below 2 s;;
assert (a3 = 7);;
let a4 = below 3 s;;
assert (a4 = 8);; 
let a5 = below 4 s;;
assert (a5 = 8);;
let a6 = below 5 s;;
assert (a6 = 9);;
let a7 = below 10 s;;
assert (a7 = 14);;
let a8 = below 16 s;;
assert (a8 = 16);;
let a9 = below 19 s;;
assert (a9 = 17);;
let a10 = below 20 s;;
assert (a10 = 18);;

let (l, _, _) = split 7 s;;
assert (not (mem 4 l));;
assert (mem 5 l);;
assert (mem 6 l);;
assert (not (mem 7 l));;
assert (not (mem 8 l));;
assert (not (mem 9 l));;
assert (not (mem 10 l));;
assert (not (mem 11 l));;

let s = add (-min_int, max_int) empty;;
let a11 = below max_int s;;
assert (a11 = max_int);;
let a12 = below 0 s;;
assert (a12 = max_int);;
let a13 = below (-1) s;;
assert (a13 = max_int);;
let a14 = below (-2) s;;
assert (a14 = max_int);;
let a15 = below (-3) s;;
assert (a15 = max_int-1);;

let s = remove (-1000, -300) s;;
let s = remove (-50, 100) s;;
let s = remove (2000, 3000) s;;

let a16 = below (-1002) s;;
let a17 = below (-1001) s;;
let a18 = below (-1000) s;;
let a19 = below (-300) s;;
let a20 = below (-299) s;;
let a21 = below (-49) s;;
let a22 = below (241) s;;
let a23 = below (842) s;;
let a24 = below (9522) s;;
let a25 = below (-825883563223485299) s;;

assert(a16 = 4611686018427386903);;
assert(a17 = 4611686018427386904);;
assert(a18 = 4611686018427386904);;
assert(a19 = 4611686018427386904);;
assert(a20 = 4611686018427386905);;
assert(a21 = 4611686018427387153);;
assert(a22 = 4611686018427387294);;
assert(a23 = 4611686018427387895);;
assert(a24 = 4611686018427387903);;
assert(a25 = 3785802455203902606);;
*)
