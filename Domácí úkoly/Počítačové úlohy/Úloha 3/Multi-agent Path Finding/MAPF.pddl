(define (domain MAPF)
    (:requirements :strips :disjunctive-preconditions)

    (:predicates
        (agent ?agentID)
        (agent-on-vertex ?agentID ?vertexID)

        (vertex ?vertexID)
        (vertex-empty ?vertexID)
        (neighbor-vertexes ?vertex1 ?vertex2)
        (distinct ?vertex1 ?vertex2)
    )

    (:action move-agent
        :parameters (?fromVertex ?toVertex ?agent)

        :precondition( and
            ( or
                (distinct ?fromVertex ?toVertex)
                (distinct ?toVertex ?fromVertex)
            )
            (vertex ?fromVertex)
            (vertex ?toVertex)
            (agent ?agent)
            (agent-on-vertex ?agent ?fromVertex)
            (vertex-empty ?toVertex)
            ( or
                (neighbor-vertexes ?fromVertex ?toVertex)
                (neighbor-vertexes ?toVertex ?fromVertex)
            )
        )

        :effect( and
            (not (agent-on-vertex ?agent ?fromVertex))
            (not (vertex-empty ?toVertex))
            (agent-on-vertex ?agent ?toVertex)
            (vertex-empty ?fromVertex)
        )
    )
)