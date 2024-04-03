(define (problem TPP_config)
    (:domain TPP)
    (:requirements :strips :equality :fluents :negative-preconditions)
    (:objects
        Albert Lidl Kaufland Tesco Billa milk bread eggs cheese chicken beef
    )
    (:init
        (= (total-expenses) 0)

        (market Albert)
        (market Lidl)
        (market Kaufland)
        (market Tesco)
        (market Billa)

        (= (path-cost Albert Lidl) 15)
        (= (path-cost Lidl Albert) 15)
        (= (path-cost Albert Kaufland) 12)
        (= (path-cost Kaufland Albert) 12)
        (= (path-cost Albert Tesco) 14)
        (= (path-cost Tesco Albert) 14)
        (= (path-cost Albert Billa) 17)
        (= (path-cost Billa Albert) 17)
        (= (path-cost Lidl Kaufland) 11)
        (= (path-cost Kaufland Lidl) 11)
        (= (path-cost Lidl Tesco) 18)
        (= (path-cost Tesco Lidl) 18)
        (= (path-cost Lidl Billa) 16)
        (= (path-cost Billa Lidl) 16)
        (= (path-cost Kaufland Tesco) 13)
        (= (path-cost Tesco Kaufland) 13)
        (= (path-cost Kaufland Billa) 19)
        (= (path-cost Billa Kaufland) 19)
        (= (path-cost Tesco Billa) 20)
        (= (path-cost Billa Tesco) 20)

        (in-market Albert)
        (visited-market Albert)

        (product milk)
        (product bread)
        (product eggs)
        (product cheese)
        (product chicken)
        (product beef)

        (= (purchased-product milk) 0)
        (= (purchased-product bread) 0)
        (= (purchased-product eggs) 0)
        (= (purchased-product cheese) 0)
        (= (purchased-product chicken) 0)
        (= (purchased-product beef) 0)

        (= (amount-to-buy milk) 10) ; 10 < 14
        (= (amount-to-buy bread) 15) ; 15 < 18
        (= (amount-to-buy eggs) 18) ; 18 < 23
        (= (amount-to-buy cheese) 11) ; 11 < 21
        (= (amount-to-buy chicken) 3) ; 3 < 15
        (= (amount-to-buy beef) 4) ; 4 < 15   Then the goal can be achieved

        ; Milk - 14
        (= (product-in-market Albert milk) 5)
        (= (product-cost Albert milk) 2.25)
        (= (product-in-market Lidl milk) 0)
        (= (product-cost Lidl milk) 3.10)
        (= (product-in-market Kaufland milk) 3)
        (= (product-cost Kaufland milk) 2.50)
        (= (product-in-market Tesco milk) 3)
        (= (product-cost Tesco milk) 2.75)
        (= (product-in-market Billa milk) 3)
        (= (product-cost Billa milk) 2.30)

        ; Bread - 18
        (= (product-in-market Albert bread) 3)
        (= (product-cost Albert bread) 3.75)
        (= (product-in-market Lidl bread) 8)
        (= (product-cost Lidl bread) 3.40)
        (= (product-in-market Kaufland bread) 0)
        (= (product-cost Kaufland bread) 4.20)
        (= (product-in-market Tesco bread) 5)
        (= (product-cost Tesco bread) 2.80)
        (= (product-in-market Billa bread) 2)
        (= (product-cost Billa bread) 4.90)

        ; Eggs - 23
        (= (product-in-market Albert eggs) 7)
        (= (product-cost Albert eggs) 4.20)
        (= (product-in-market Lidl eggs) 0)
        (= (product-cost Lidl eggs) 3.60)
        (= (product-in-market Kaufland eggs) 5)
        (= (product-cost Kaufland eggs) 2.90)
        (= (product-in-market Tesco eggs) 3)
        (= (product-cost Tesco eggs) 4.50)
        (= (product-in-market Billa eggs) 8)
        (= (product-cost Billa eggs) 3.10)

        ; Cheese - 21
        (= (product-in-market Albert cheese) 2)
        (= (product-cost Albert cheese) 4.80)
        (= (product-in-market Lidl cheese) 6)
        (= (product-cost Lidl cheese) 3.30)
        (= (product-in-market Kaufland cheese) 0)
        (= (product-cost Kaufland cheese) 4.90)
        (= (product-in-market Tesco cheese) 4)
        (= (product-cost Tesco cheese) 2.70)
        (= (product-in-market Billa cheese) 9)
        (= (product-cost Billa cheese) 3.60)

        ; Chicken - 15
        (= (product-in-market Albert chicken) 1)
        (= (product-cost Albert chicken) 3.90)
        (= (product-in-market Lidl chicken) 4)
        (= (product-cost Lidl chicken) 4.20)
        (= (product-in-market Kaufland chicken) 7)
        (= (product-cost Kaufland chicken) 3.50)
        (= (product-in-market Tesco chicken) 0)
        (= (product-cost Tesco chicken) 5.10)
        (= (product-in-market Billa chicken) 3)
        (= (product-cost Billa chicken) 4.80)

        ; Beef - 15
        (= (product-in-market Albert beef) 5)
        (= (product-cost Albert beef) 4.50)
        (= (product-in-market Lidl beef) 0)
        (= (product-cost Lidl beef) 3.80)
        (= (product-in-market Kaufland beef) 2)
        (= (product-cost Kaufland beef) 5.20)
        (= (product-in-market Tesco beef) 8)
        (= (product-cost Tesco beef) 3.90)
        (= (product-in-market Billa beef) 0)
        (= (product-cost Billa beef) 4.70)
    )

    (:goal( and
            (bought-product milk)
            (bought-product bread)
            (bought-product eggs)
            (bought-product cheese)
            (bought-product chicken)
            (bought-product beef)
        )
    )

    (:metric minimize
        (total-expenses)
    )
)