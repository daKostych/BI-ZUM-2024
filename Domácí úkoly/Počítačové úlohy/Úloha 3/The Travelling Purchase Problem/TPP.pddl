(define (domain TPP)
    (:requirements :strips :equality :fluents :negative-preconditions)
    (:predicates
        (product ?productName)
        (bought-product ?productName)

        (market ?market)
        (in-market ?market)
        (visited-market ?market)
    )
    (:functions
        (total-expenses)

        (path-cost ?fromMarket ?toMarket)

        (purchased-product ?productName)
        (amount-to-buy ?productName)
        (product-in-market ?market ?productName)
        (product-cost ?market ?productName)
    )
    (:action move
        :parameters (?from ?to)

        :precondition( and
            (not (= ?from ?to))
            (market ?from)
            (market ?to)
            (in-market ?from)
            (not (visited-market ?to))
        )

        :effect( and
            (not (in-market ?from))
            (in-market ?to)
            (visited-market ?to)
            (increase (total-expenses) (path-cost ?from ?to))
        )
    )
    (:action buy
        :parameters(?market ?product)

        :precondition( and
            (market ?market)
            (product ?product)
            (in-market ?market)
            (>= (product-in-market ?market ?product) 1)
        )

        :effect( and
            (increase
                (total-expenses)
                (product-cost ?market ?product))
            (increase (purchased-product ?product) 1)
            (decrease (product-in-market ?market ?product) 1)
        )
    )
    (:action delete-product
        :parameters (?product)

        :precondition (and
            (product ?product)
            (not (bought-product ?product))
            (>= (purchased-product ?product) (amount-to-buy ?product))
        )

        :effect (and
            (bought-product ?product)
        )
    )
)