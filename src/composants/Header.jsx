import React from 'react'
import { FiUsers } from 'react-icons/fi';
import { Outlet, Link } from "react-router-dom";
import '../App.css';


const Header = () => {

  return (
    <div className='main1'>
      <div className='mainnav'>

        <Link className='navs Btn nav1' to="/ChoixQcm">
          Choix de Qcm
        </Link>

        <Link className='navs Btn nav2   Btn1 ' to="/Create">
          Create
        </Link>

        <Link className='user1' to="/User">
            <FiUsers className='imguser'/>
        </Link>
      </div>

      <div className='secondarynav'>

      </div>
    </div>
  )

}

export default Header