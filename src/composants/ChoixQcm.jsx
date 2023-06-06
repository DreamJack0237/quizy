import React from 'react'
import Header from './Header'
import { Outlet, Link } from "react-router-dom";

const ChoixQcm = () => {
  return (
    <div className='flex'>
    <Header />
    <div className='justify'>
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

        <div className='Question '>
            <Link to="/Qcm" className='choix'>
                Lorem ipsum dolor sit amet consectetur, adipisicing elit. Illo, veniam.
            </Link>
        </div>

        
    </div>


</div>
  )
}

export default ChoixQcm