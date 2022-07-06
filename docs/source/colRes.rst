Collision Resolution
====================

Once a collision has be detected, we need to pull the object appart.
For this, we will apply an impulse on the objects to move them.

For this, we recieve two informations to solve it :

- The collision normal
- The penetration depth

The collision normal is the direction in which the impulse will be applied and
the penetration depth says by how much we will move the objects.

Since we know the direction of our impulse, we only need to solve the magnitude of it.

Let's look at the equations we will use in this process.

.. math::

    V_{ab} = V_{b} - V_{a}

This creates a vector from position a to position b.
It gives us the relative velocity from a to b.
We want to know the relative velocity along the collision normal. For this we do :

.. math::

    V_{ab} \cdot n = (V_b - V_a) \cdot n

The next important thing I'll mention is the *coefficient of restitution*.
The restitution can be seen as the ability of an object to "bounce".
The restitution is noted :math:`e` and is a value between :math:`0` and :math:`1`.

The restitution used is computed by multiplying the restitution of both objects :

.. math::

    e = e_a \cdot e_b

Newton's Law of Restitution states the following :

.. math::

    V' = e \cdot V

This means that the velocity after the collision is the velocity before multiplied by the coefficient of restitution.

From this, we can add the restitution to our current equation :

.. math::

    V_{ab} \cdot n = -e \cdot (V_b - V_a) \cdot n

The coefficient is negative because the bounce is in the opposite direction of the movement.
This is represented by putting the coefficient in negative.

If we want to express these velocities with an impulse, it is done with :

.. math::

    V' = V + j \cdot n

Here we move the vector :math:`V` by an amount of :math:`j` in the direction of :math:`n`.

There is still one thing we don't take into account here : the mass.
An impulse is a change in momentum and momentum is `mass * velocity`. 
Here is how it's done with mass :

.. math::

    impulse = mass * velocity

.. math::

    velocity = \frac{impulse}{mass}

.. math::

    V' = V + \frac{j \cdot n}{mass}

This is good, but we need to represent it with two objects.

.. math::

    V'_a = V_a + \frac{j \cdot n}{mass}

.. math::

    V'_b = V_a - \frac{j \cdot n}{mass}

Finally, we merge our final equations to get this :

.. math::

    (V_a - V_v + \frac{j \cdot n}{mass_a} + \frac{j \cdot n}{mass_b}) \cdot n = -e \cdot (V_b - V_a) \cdot n

.. math::

    (V_a - V_v + \frac{j \cdot n}{mass_a} + \frac{j \cdot n}{mass_b}) \cdot n + e \cdot (V_b - V_a) \cdot n = 0

But what we want is only the magnitude, so :math:`j`.

.. math::

    (V_b - V_a) \cdot n + j \cdot (\frac{j \cdot n}{mass_a} + \frac{j \cdot n}{mass_b}) \cdot n + e \cdot (V_b - V_a) \cdot n = 0

.. math::

    (1 + e)((V_b - V_a) \cdot n) + j \cdot (\frac{j \cdot n}{mass_a} + \frac{j \cdot n}{mass_b}) \cdot n = 0

.. math::

    j = \frac{-(1 + e)((V_b - V_a) \cdot n)}{\frac{1}{mass_a} + \frac{1}{mass_b}}

Here is the math for the impulse solver !

The code has a bit more to it, especially some checks to speed things up, but the logic is the same.