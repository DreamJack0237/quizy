import React from 'react'
import {
    Link,
    Routes,
    Route,
    useNavigate,
  } from 'react-router-dom'; 

const User = () => {

    const navigate = useNavigate();
    return (
        <div>
            <form action="get">
                <div className='flex user' name="sign">
                    
                    <label for="sign">Signup </label>
                    <input type="text" placeholder="Usermail.." />
                    <input type="email" placeholder="Usermail..." />
                    <input type="text" placeholder="Password..." />
                    <button className='Btn'>submit</button>
                </div>


            </form>

            <div className='center margint'>
                <button className='Btn exite' onClick={() => navigate(-1)}>Go back / Exite</button>
            </div>

        </div>
    )
}

export default User