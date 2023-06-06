import React from 'react'
import { FiMenu } from 'react-icons/fi';
import { Outlet, Link } from "react-router-dom";
import '../App.css';


const Header = () => {
  return (
    <div>
      <div className='mainnav'>

        <Link className='navs Btn' to="/Qcm">
          <button className='nav1'>
            Qcm
          </button>
        </Link>

        <Link className='navs Btn' to="/Create">
          <button className='nav2 navs Btn1 '>
            Create
          </button>
        </Link>

        <div className="Fimenu">
          <FiMenu />
        </div>

      </div>
    </div>

  )
}

export default Header