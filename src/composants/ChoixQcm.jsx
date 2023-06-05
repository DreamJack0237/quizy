import React from 'react'
import Header from './Header'
import { Outlet, Link } from "react-router-dom";

const ChoixQcm = () => {
  return (
    <div className='flex'>
    <Header />
    <div>
        <div className='Question '>
            <Link to="/Qcm" className='choix'>
                Introduction aux algorithmiques
            </Link>
        </div>

        <div className='Question '>
            <Link to="/Qcm" className='choix'>
                programation c++
            </Link>
        </div>

        
    </div>


</div>
  )
}

export default ChoixQcm